#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define MAXN 30000
#define MAXW (MAXN / 64 + 2)

static unsigned char col[MAXN + 1];
static int tabu[MAXN + 1];
static uint64_t X[2][MAXW];
static int N, WN;

static int tgt, lo, hi;
static long nodes;
long lvl[6];
static long hits;
static int cur[5];
static int fset[5];
static int single;
static int sums[32];
static int nsums;

static uint64_t rs = 88172645463325252ULL;
static uint64_t rnd(void) {
    rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17;
    return rs;
}

static inline void bs_set(int t, int i) { X[t][i >> 6] |= 1ULL << (i & 63); }
static inline void bs_clr(int t, int i) { X[t][i >> 6] &= ~(1ULL << (i & 63)); }

static void flip(int x) {
    if (col[x]) { bs_clr(1, x); bs_set(0, x); col[x] = 0; }
    else { bs_clr(0, x); bs_set(1, x); col[x] = 1; }
}

static void build_mask(uint64_t *w, int t, int last, int e_hi, int *pwlo, int *pwhi) {
    int wlo = (last + 1) >> 6, whi = e_hi >> 6;
    if (wlo < 0) wlo = 0;
    if (whi >= WN) whi = WN - 1;
    if (wlo > whi) { *pwlo = 1; *pwhi = 0; return; }
    for (int i = wlo; i <= whi; i++) w[i] = X[t][i];
    int lb = (last + 1) & 63;
    w[wlo] = (lb == 0) ? w[wlo] : (w[wlo] & (~0ULL << lb));
    int hb = e_hi & 63;
    w[whi] = (hb >= 63) ? w[whi] : (w[whi] & ((1ULL << (hb + 1)) - 1));
    for (int k = 0; k < nsums; k++) {
        int s = sums[k];
        int ws = s >> 6, bs = s & 63;
        for (int i = wlo; i <= whi; i++) {
            uint64_t v = (i + ws < WN) ? (X[t][i + ws] >> bs) : 0ULL;
            if (bs && i + ws + 1 < WN) v |= X[t][i + ws + 1] << (64 - bs);
            w[i] &= v;
        }
    }
    *pwlo = wlo; *pwhi = whi;
}

static uint64_t work[6][MAXW];
static void rec(int size, int last, int total);
static void rebuild(int n);

static void rec(int size, int last, int total) {
    if (size == 5) {
        if (total >= lo && total <= hi) {
            if (hits == 0) memcpy(fset, cur, sizeof fset);
            hits++;
            if (single) nodes = -1;
        }
        return;
    }
    nodes++; lvl[size]++;
    int rem = 5 - size;
    long e_hi = ((long)N - total - (long)(rem - 1) * rem / 2) / rem;
    if (e_hi > N) e_hi = N;
    if (e_hi <= last) return;

    if (rem == 1 && lo == hi) {
        int e = hi - total;
        if (e <= last || e > N) return;
        if (col[e] != tgt) return;
        for (int i = 0; i < nsums; i++) if (col[e + sums[i]] != tgt) return;
        cur[size] = e;
        if (hits == 0) memcpy(fset, cur, sizeof fset);
        hits++;
        if (single) nodes = -1;
        return;
    }

    uint64_t *w = work[size];
    int wlo, whi;
    build_mask(w, tgt, last, (int)e_hi, &wlo, &whi);
    for (int i = wlo; i <= whi; i++) {
        uint64_t bits = w[i];
        while (bits) {
            int b = __builtin_ctzll(bits);
            bits &= bits - 1;
            int e = (i << 6) + b;
            if (e <= last || e > e_hi) continue;
            int old = nsums;
            for (int j = 0; j < old; j++) sums[nsums++] = sums[j] + e;
            sums[nsums++] = e;
            cur[size] = e;
            rec(size + 1, e, total + e);
            nsums = old;
            if (nodes < 0) return;
        }
    }
}

static long scan_x(int t, int x, int stop_first) {
    tgt = t; lo = 1; hi = N; hits = 0; nodes = 0; single = stop_first;
    nsums = 0;
    if (col[x] != t) return 0;
    cur[0] = x;
    sums[nsums++] = x;
    rec(1, x, x);
    return hits;
}

static int find_viol_x(int x, int *out) {
    for (int t = 0; t < 2; t++) {
        if (scan_x(t, x, 1) > 0) { memcpy(out, fset, sizeof fset); return 1; }
    }
    return 0;
}

static long scan(int t, int l, int h, int stop_first) {
    tgt = t; lo = l; hi = h; hits = 0; nodes = 0; nsums = 0; single = stop_first;
    rec(0, 0, 0);
    return hits;
}

static int find_viol(int l, int h, int *out) {
    for (int t = 0; t < 2; t++) {
        if (scan(t, l, h, 1) > 0) { memcpy(out, fset, sizeof fset); return 1; }
    }
    return 0;
}

static void write_witness(int best) {
    char path[256];
    snprintf(path, sizeof path, "witnesses/k5_w%d.txt", best);
    FILE *f = fopen(path, "w");
    if (!f) { perror("fopen"); return; }
    for (int i = 1; i <= best; i++) fputc(col[i] ? '1' : '0', f);
    fputc('\n', f);
    fclose(f);
}



static long count_all(int n) { return scan(0, 1, n, 0) + scan(1, 1, n, 0); }

static long score_flip(int x, int n) {
    flip(x);
    long s = count_all(n);
    flip(x);
    return s;
}

static int build_cands(const int *A, int n, int *cand) {
    int nc = 0;
    for (int m = 1; m < 32; m++) {
        int t = 0;
        for (int j = 0; j < 5; j++) if (m >> j & 1) t += A[j];
        if (t < 1 || t > n) continue;
        int dup = 0;
        for (int k = 0; k < nc; k++) if (cand[k] == t) { dup = 1; break; }
        if (!dup) cand[nc++] = t;
    }
    int dup = 0;
    for (int k = 0; k < nc; k++) if (cand[k] == n) dup = 1;
    if (!dup && n >= 1) cand[nc++] = n;
    return nc;
}

static int do_step(int N, long maxiter) {
    bs_set(0, N); col[N] = 0;
    int A[5];
    int bad = 0;
    if (find_viol(N, N, A)) { flip(N); bad = find_viol(N, N, A); }
    long it = 0, stag = 0;
    memset(tabu, 0, (size_t)(N + 1) * sizeof(int));
    while (bad) {
        if (++it > maxiter) {
            long c0 = scan(0, 1, N, 0), c1 = scan(1, 1, N, 0);
            printf("FAILSTEP N=%d it=%ld viol=%ld+%ld\n", N, it, c0, c1);
            return 0;
        }
        int cand[40];
        int nc = build_cands(A, N, cand);
        long cur = count_all(N);
        long bestsc = -1; int bestx = -1;
        for (int j = 0; j < 5; j++) {
            int c = A[j];
            if (tabu[c] > it) continue;
            long sc = score_flip(c, N);
            if (bestx < 0 || sc < bestsc) { bestsc = sc; bestx = c; }
        }
        if (bestx < 0 || bestsc >= cur) {
            int off = (int)(rnd() % nc);
            for (int q = 0; q < nc; q++) {
                int c = cand[(q + off) % nc];
                if (c == A[0] || c == A[1] || c == A[2] || c == A[3] || c == A[4]) continue;
                if (tabu[c] > it) continue;
                long sc = score_flip(c, N);
                if (bestx < 0 || sc < bestsc) { bestsc = sc; bestx = c; }
                if (sc < cur) break;
            }
        }
        if (bestx < 0) bestx = cand[rnd() % nc];
        flip(bestx);
        tabu[bestx] = (int)(it + 4 + (rnd() % 7));
        bad = find_viol_x(bestx, A);
        if (!bad) bad = find_viol(1, N, A);
        if (getenv("K5DBG") && it % 100 == 0) {
            long c0 = scan(0, 1, N, 0), c1 = scan(1, 1, N, 0);
            printf("  N=%d it=%ld sc=%ld viol=%ld stag=%ld\n", N, it, bestsc, c0 + c1, stag);
            fflush(stdout);
        }
        if (bestsc > 0) {
            if (++stag > 300) {
                int k = 3 + (int)(rnd() % 4);
                for (int q = 0; q < k; q++) { int x = 1 + (int)(rnd() % N); flip(x); tabu[x] = (int)(it + 5); }
                stag = 0;
                bad = find_viol(1, N, A);
            }
        } else stag = 0;
    }
    return 1;
}


static int run_fixed(int n, long maxit, const char *seedfile, long report) {
    N = n; WN = (n >> 6) + 2;
    memset(X, 0, sizeof X);
    memset(col, 0, (size_t)n + 1);
    int n0 = 0;
    if (seedfile) {
        FILE *f = fopen(seedfile, "r");
        if (!f) { perror("seedfile"); return 0; }
        int ch;
        while ((ch = fgetc(f)) != EOF && n0 < n) {
            if (ch == '0' || ch == '1') col[++n0] = (unsigned char)(ch - '0');
        }
        fclose(f);
        if (n0 > n) n0 = n;
    }
    for (int i = n0 + 1; i <= n; i++) col[i] = (unsigned char)(rnd() & 1);
    rebuild(n);
    long it = 0;
    int A[5];
    memset(tabu, 0, (size_t)(n + 1) * sizeof(int));
    long bestv = -1;
    while (it < maxit) {
        if (!find_viol(1, n, A)) { printf("SOLVED n=%d it=%ld\n", n, it); return 1; }
        it++;
        int cand[40];
        int nc = build_cands(A, n, cand);
        long cur = count_all(n);
        long bestsc = -1; int bestx = -1;
        for (int j = 0; j < 5; j++) {
            int c = A[j];
            if (tabu[c] > it) continue;
            long sc = score_flip(c, n);
            if (bestx < 0 || sc < bestsc || (sc == bestsc && (rnd() & 1))) { bestsc = sc; bestx = c; }
        }
        if (bestx < 0 || bestsc >= cur) {
            for (int j = 0; j < nc; j++) {
                int c = cand[j];
                if (c == A[0] || c == A[1] || c == A[2] || c == A[3] || c == A[4]) continue;
                if (tabu[c] > it) continue;
                long sc = score_flip(c, n);
                if (sc < bestsc) { bestsc = sc; bestx = c; }
                if (sc < cur) break;
            }
        }
        if (bestx < 0) bestx = cand[rnd() % nc];
        flip(bestx);
        tabu[bestx] = (int)(it + 4 + (rnd() % 7));
        if (report && it % report == 0) {
            long c0 = scan(0, 1, n, 0), c1 = scan(1, 1, n, 0);
            if (bestv < 0 || c0 + c1 < bestv) bestv = c0 + c1;
            printf("it=%ld viol=%ld best=%ld\n", it, c0 + c1, bestv);
            fflush(stdout);
        }
    }
    long c0 = scan(0, 1, n, 0), c1 = scan(1, 1, n, 0);
    printf("TIMEOUT n=%d it=%ld viol=%ld\n", n, it, c0 + c1);
    return 0;
}

static void rebuild(int n) {
    memset(X, 0, sizeof X);
    for (int i = 1; i <= n; i++) bs_set(col[i], i);
}

int main(int argc, char **argv) {
    if (argc >= 2 && strcmp(argv[1], "fix") == 0) {
        if (argc < 3) { fprintf(stderr, "usage: %s fix N [iters] [seedfile] [seed]\n", argv[0]); return 2; }
        int n = atoi(argv[2]);
        long iters = (argc > 3) ? atol(argv[3]) : 200000;
        const char *sf = (argc > 4 && strcmp(argv[4], "-")) ? argv[4] : NULL;
        if (argc > 5) rs = strtoull(argv[5], NULL, 10) | 1;
        int r = run_fixed(n, iters, sf, 1000);
        if (r) {
            char path[256];
            snprintf(path, sizeof path, "witnesses/k5_w%d.txt", n);
            FILE *f = fopen(path, "w");
            for (int i = 1; i <= n; i++) fputc(col[i] ? '1' : '0', f);
            fputc('\n', f);
            fclose(f);
            printf("wrote %s\n", path);
        }
        return r ? 0 : 1;
    }
    if (argc < 2) { fprintf(stderr, "usage: %s NMAX [seed]\n", argv[0]); return 2; }
    int nmax = atoi(argv[1]);
    if (nmax < 20 || nmax > MAXN) { fprintf(stderr, "bad NMAX\n"); return 2; }
    if (argc > 2) rs = strtoull(argv[2], NULL, 10) | 1;

    clock_t t0 = clock();
    N = nmax; WN = (nmax >> 6) + 2;
    unsigned char *snap = malloc((size_t)nmax + 1);
    if (!snap) { perror("malloc"); return 2; }
    col[1] = (unsigned char)(rnd() & 1);
    bs_set(col[1], 1);

    int best = 1;
    long maxiter = 3000;

    for (N = 2; N <= nmax; N++) {
        memcpy(snap, col, (size_t)N);
        int ok = 0;
        for (int attempt = 0; attempt < 5 && !ok; attempt++) {
            if (attempt) {
                memcpy(col, snap, (size_t)N);
                rebuild(N);
                col[N] = (unsigned char)(rnd() & 1);
                bs_set(col[N], N);
            }
            ok = do_step(N, maxiter);
        }
        if (!ok) { memcpy(col, snap, (size_t)N); best = N - 1; break; }
        best = N;
        if (N % 100 == 0) {
            double el = (double)(clock() - t0) / CLOCKS_PER_SEC;
            printf("N=%d time=%.1fs speed=%.1f N/s\n", N, el, N / el);
            fflush(stdout);
            int vv[5];
            if (find_viol(1, N, vv)) { printf("CHECKPOINT FAILED at %d\n", N); return 1; }
            write_witness(best);
        }
    }

    N = best;
    rebuild(best);
    int chk[5];
    if (find_viol(1, best, chk)) { printf("INTERNAL CHECK FAILED at %d\n", best); free(snap); return 1; }
    printf("BEST=%d\n", best);
    write_witness(best);
    printf("wrote witnesses/k5_w%d.txt\n", best);
    free(snap);
    return 0;
}
