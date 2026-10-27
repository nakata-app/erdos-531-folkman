/* independent check: 2-colouring of {1..N}; report any 5-set {a<b<c<d<e}, a+b+c+d+e<=N, whose 31 nonempty
   subset sums all have one colour. prefix pruning only (every subset sum of a prefix must already match). */
#include <stdio.h>
#include <stdlib.h>
static int col[400005], N;
static int sums[32], ns, sel[5];
static long found;
static void rec(int depth, int last, int total) {
    if (depth == 5) { found++; if (found <= 3) printf("MONO %d %d %d %d %d\n", sel[0], sel[1], sel[2], sel[3], sel[4]); return; }
    int rem = 5 - depth;
    for (int e = last + 1; ; e++) {
        int minrest = 0; for (int j = 1; j < rem; j++) minrest += e + j;   /* smallest completions */
        if (total + e + minrest > N) break;
        int t = col[sel[0] ? sel[0] : e]; int ok = (col[e] == t);
        for (int i = 0; ok && i < ns; i++) ok = (col[sums[i] + e] == t);
        if (!ok) continue;
        int base = ns; for (int i = 0; i < base; i++) sums[ns++] = sums[i] + e; sums[ns++] = e;
        sel[depth] = e; rec(depth + 1, e, total + e); sel[depth] = 0; ns = base;
    }
}
int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r"); int ch; N = 0;
    while ((ch = fgetc(f)) != EOF) if (ch == '0' || ch == '1') col[++N] = ch - '0';
    rec(0, 0, 0);
    printf("N=%d mono5=%ld\n", N, found); return found ? 1 : 0;
}
