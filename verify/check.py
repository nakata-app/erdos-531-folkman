import sys
from itertools import combinations

def main(path):
    s = "".join(ch for ch in open(path).read() if not ch.isspace())
    if set(s) - {"0", "1"}:
        sys.exit("bad char")
    n = len(s)
    col = [None] + [int(ch) for ch in s]
    tested = mono = 0
    for a in range(1, n + 1):
        for b in range(a + 1, n + 1 - a):
            for c in range(b + 1, n + 1 - a - b):
                for d in range(c + 1, n + 1 - a - b - c):
                    tested += 1
                    A = (a, b, c, d)
                    k = col[a]
                    if all(col[sum(T)] == k for r in range(1, 5) for T in combinations(A, r)):
                        if not mono:
                            print("counterexample", *A)
                        mono += 1
    print(f"N={n} tested={tested} mono={mono}")
    sys.exit(1 if mono else 0)

main(sys.argv[1])
