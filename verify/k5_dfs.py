import sys


def bad_sets(col, N, t, stop_after=0, lo=1, hi=None):
    if hi is None:
        hi = N
    out = []
    chosen = []
    partial = []

    def rec(total, last):
        if len(chosen) == 5:
            if lo <= total <= hi:
                out.append(tuple(chosen))
                if stop_after and len(out) >= stop_after:
                    raise StopIteration
            return
        rem = 5 - len(chosen)
        e_hi = (N - total - (rem - 1) * rem // 2) // rem
        for e in range(last + 1, e_hi + 1):
            if col[e] != t:
                continue
            if any(col[e + s] != t for s in partial):
                continue
            base = len(partial)
            for i in range(base):
                partial.append(partial[i] + e)
            partial.append(e)
            chosen.append(e)
            rec(total + e, e)
            del chosen[-1]
            del partial[base:]

    try:
        rec(0, 0)
    except StopIteration:
        pass
    return out


def main():
    path = sys.argv[1]
    s = "".join(ch for ch in open(path).read() if ch in "01")
    col = [0] + [int(ch) for ch in s]
    N = len(s)
    total = 0
    for t in (0, 1):
        b = bad_sets(col, N, t)
        print(f"colour {t}: {len(b)} monochromatic 5-sets")
        for x in b[:3]:
            print("  ", x, "sum", sum(x))
        total += len(b)
    print(f"N={N} mono_total={total}")
    return 1 if total else 0


if __name__ == "__main__":
    sys.exit(main())
