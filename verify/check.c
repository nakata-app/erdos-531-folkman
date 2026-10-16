#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "usage: %s coloring.txt\n", argv[0]); return 2; }
    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("fopen"); return 2; }
    static int col[100001];
    int n = 0, ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '0' || ch == '1') { if (n >= 100000) return 2; col[++n] = ch - '0'; }
        else if (ch != '\n' && ch != '\r' && ch != ' ') { fprintf(stderr, "bad char\n"); return 2; }
    }
    fclose(f);
    long tested = 0, mono = 0;
    for (int a = 1; a <= n; a++)
    for (int b = a + 1; a + b <= n; b++)
    for (int c = b + 1; a + b + c <= n; c++)
    for (int d = c + 1; a + b + c + d <= n; d++) {
        int e[4] = {a, b, c, d}, k = col[a], ok = 1;
        tested++;
        for (int m = 1; m < 16 && ok; m++) {
            int t = 0;
            for (int j = 0; j < 4; j++) if (m >> j & 1) t += e[j];
            if (col[t] != k) ok = 0;
        }
        if (ok) { if (!mono) printf("counterexample %d %d %d %d\n", a, b, c, d); mono++; }
    }
    printf("N=%d tested=%ld mono=%ld\n", n, tested, mono);
    return mono ? 1 : 0;
}
