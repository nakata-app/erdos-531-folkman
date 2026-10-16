# Erdős Problem #531: a lower bound F(4) ≥ 375

## The problem

From [erdosproblems.com/531](https://www.erdosproblems.com/531):

> Let $F(k)$ be the minimal $N$ such that if we two-colour $\{1,\ldots,N\}$ there is a set $A$ of size $k$ such that all subset sums $\sum_{a\in S}a$ (for $\emptyset\neq S\subseteq A$) are monochromatic. Estimate $F(k)$.

A colour is only defined on {1, …, N}, so a set A counts only when sum(A) ≤ N. The elements of A are distinct.

## The result

`witnesses/w374.txt` is a 2-colouring of {1, …, 374}. Character i (counting from 1) is the colour of the integer i. No set {a < b < c < d} with a + b + c + d ≤ 374 has all 15 nonempty subset sums the same colour. Therefore

**F(4) ≥ 375.**

| Witness              | Length | SHA-256                                                            |
| -------------------- | ------ | ------------------------------------------------------------------ |
| `witnesses/w305.txt` | 305    | (see git history)                                                  |
| `witnesses/w331.txt` | 331    | `1b353273ad6d01bca28f5bbe6a73d5d9542f0314c98960ff396475118372490a` |
| `witnesses/w372.txt` | 372    | `ea2bf6e5615e3c95d79f0403b73dc00664147865cb879558f24fbc2cec256e53` |
| `witnesses/w373.txt` | 373    | `f3c5807e1bf958cd6690dd7c2be35a9bc186008a7919e586a369f6de0ebd0e09` |
| `witnesses/w374.txt` | 374    | `143af24f8fd894962ff190c0eade9aae2111f2e42528d4d9054001fc726b9cfe` |

As far as we could find, the best previously reported value was F(4) ≥ 201, in a working report on [erdosproblemaday.com](https://erdosproblemaday.com/problem/531) maintained by Patrick White. We found no value of F(4) on erdosproblems.com, in the OEIS, or in the published literature. Please open an issue if you know of one.

This is a lower bound only. It says nothing about the exact value of F(4). Showing that F(4) = N requires proving that every 2-colouring of {1, …, N} contains such a set, for example with a SAT solver and a checked unsatisfiability proof. We have not done that.

## Verify it yourself

The check is self-contained and takes about a second in C.

```sh
shasum -a 256 witnesses/w374.txt
cc -O2 -o check verify/check.c
./check witnesses/w374.txt
```

Expected output:

```
N=374 tested=32358327 mono=0
```

A dependency-free Python checker gives the same result more slowly:

```sh
python3 verify/check.py witnesses/w374.txt
```

Both checkers print the first monochromatic set they find and exit with status 1 if there is one. As a sanity check, an all-zero string of length 374 makes every set monochromatic: `tested=32358327 mono=32358327`.

## Small values

| k   | Value      | Status                                                                                                                                |
| --- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| 2   | F(2) = 9   | Equals the weak Schur number WS(2) + 1.                                                                                               |
| 3   | F(3) = 54  | Reported first by [erdosproblemaday.com](https://erdosproblemaday.com/report/531) with an LRAT proof. We reproduced it independently. |
| 4   | F(4) ≥ 375 | This repository.                                                                                                                      |

Our reproduction of F(3) = 54 used our own encoder, `verify/cnf.py`. It writes one pair of clauses for each set: the subset sums are not all colour 0, and they are not all colour 1. It uses no symmetry breaking. CaDiCaL finds a colouring for N = 53, and its model was checked directly. CaDiCaL reports N = 54 unsatisfiable, drat-trim verifies its DRAT proof, and Kissat agrees. The same encoder gives F(2) = 9, with a drat-trim-verified proof for N = 9.

```sh
python3 verify/cnf.py 54 3 > n54.cnf
cadical n54.cnf n54.drat --no-binary
drat-trim n54.cnf n54.drat
```

## How the witness was found

The colourings were found by autonomous AI research agents. They used a SAT encoding with CaDiCaL and Kissat to reach N = 263. After that, min-conflicts local search with tabu, WalkSAT-style noise and large random perturbations (60 or more bits at once) extended each colouring to the next N, starting from the previous witness. Smaller perturbations stalled at N = 305. Several separately written checkers, in C and Python, confirmed the witnesses. They all ran on one machine, so they are independent implementations, not independent hardware.

As an independent re-verification, every witness produced by the agent chain, w200–w374 (124 files), was re-checked with a further separately written brute-force C verifier, `verify/f4_check.c`, which enumerates the same quadruple subset sums directly without any SAT dependency: every file reports `mono_cubes=0`. The full re-check log is kept at [validation.log](validation.log).

## Licence

The witness data is dedicated to the public domain under CC0 1.0. The checkers are released under the MIT licence.
