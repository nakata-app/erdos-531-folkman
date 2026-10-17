# Erdős Problem #531: a lower bound F(4) ≥ 389

## The problem

From [erdosproblems.com/531](https://www.erdosproblems.com/531):

> Let $F(k)$ be the minimal $N$ such that if we two-colour $\{1,\ldots,N\}$ there is a set $A$ of size $k$ such that all subset sums $\sum_{a\in S}a$ (for $\emptyset\neq S\subseteq A$) are monochromatic. Estimate $F(k)$.

A colour is only defined on {1, …, N}, so a set A counts only when sum(A) ≤ N. The elements of A are distinct.

## The result

`witnesses/w388.txt` is a 2-colouring of {1, …, 388}. Character i (counting from 1) is the colour of the integer i. No set {a < b < c < d} with a + b + c + d ≤ 388 has all 15 nonempty subset sums the same colour. Therefore

**F(4) ≥ 389.**

| Witness              | Length | SHA-256                                                            |
| -------------------- | ------ | ------------------------------------------------------------------ |
| `witnesses/w331.txt` | 331    | `1b353273ad6d01bca28f5bbe6a73d5d9542f0314c98960ff396475118372490a` |
| `witnesses/w372.txt` | 372    | `ea2bf6e5615e3c95d79f0403b73dc00664147865cb879558f24fbc2cec256e53` |
| `witnesses/w373.txt` | 373    | `f3c5807e1bf958cd6690dd7c2be35a9bc186008a7919e586a369f6de0ebd0e09` |
| `witnesses/w374.txt` | 374    | `143af24f8fd894962ff190c0eade9aae2111f2e42528d4d9054001fc726b9cfe` |
| `witnesses/w375.txt` | 375    | `737e515922693cddf6ec2fcc0433a384f4cdcafb3c3dac22a0c3306660a005f2` |
| `witnesses/w376.txt` | 376    | `020e2d3c956915836ab95978c092f3bad0e89d366406781b0fdbee478ea01b2c` |
| `witnesses/w377.txt` | 377    | `5a53d2e3ecdee3968fa67e741aa6988922282a9421f43d84ef7b525df1c9d232` |
| `witnesses/w378.txt` | 378    | `9dfaf4ca826b0004dc99fbda944785f55b9a83ce81036e52b2b2e72ef7b18995` |
| `witnesses/w379.txt` | 379    | `2c4814215f07b054fe48c94191df592c2fec293c17cfb8d61b831d53e4d3e058` |
| `witnesses/w380.txt` | 380    | `30ad7b9d6105ad22a443d696469ec4c88f35c34f972c07460b96cd2a4eb02737` |
| `witnesses/w381.txt` | 381    | `68bcfe2263d028982e8bb495d447e0ae909acdf23986cd28946c5c55c20b20be` |
| `witnesses/w382.txt` | 382    | `deaf8b3febd77ae324386d2fa088ef681d75999d9fa98b65d936f1acf2235906` |
| `witnesses/w383.txt` | 383    | `c9aae3d7baa8b68c0a3c37a506dfa7916a2ffe15fe8661b9c8a32e97464710ae` |
| `witnesses/w384.txt` | 384    | `229681213ccfed4b76d53314c51a92cdedf06a26913509e85f7de5eeca0b0a2b` |
| `witnesses/w385.txt` | 385    | `4216fadd4ff6548b26ab433b5f6ce200f23d11272d969f7ab33cfca080dd92c2` |
| `witnesses/w386.txt` | 386    | `0681020ee8b42d40cfdc09af0933c06af1f141cd446248227e9681ff9878229f` |
| `witnesses/w387.txt` | 387    | `44ba077c07fbef9c25b8f3bd200bc7d4fd81663aa70b8f527f4471ec0ba4ff03` |
| `witnesses/w388.txt` | 388    | `c4c1b4dc5daaea6cb80718b12879f11aaee661447ea769420d5c11086b49b0b4` |

As far as we could find, the best previously reported value was F(4) ≥ 201, in a working report on [erdosproblemaday.com](https://erdosproblemaday.com/problem/531) maintained by Patrick White. We found no value of F(4) on erdosproblems.com, in the OEIS, or in the published literature. Please open an issue if you know of one.

This is a lower bound only. It says nothing about the exact value of F(4). Showing that F(4) = N requires proving that every 2-colouring of {1, …, N} contains such a set, for example with a SAT solver and a checked unsatisfiability proof. We have not done that.

## Verify it yourself

The check is self-contained and takes about a second in C.

```sh
shasum -a 256 witnesses/w388.txt
cc -O2 -o check verify/check.c
./check witnesses/w388.txt
```

Expected output:

```
N=388 tested=37548560 mono=0
```

A dependency-free Python checker gives the same result more slowly:

```sh
python3 verify/check.py witnesses/w388.txt
```

Both checkers print the first monochromatic set they find and exit with status 1 if there is one. As a sanity check, an all-zero string of length 388 makes every set monochromatic: `tested=37548560 mono=37548560`.

## Small values

| k   | Value      | Status                                                                                                                                |
| --- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| 2   | F(2) = 9   | Equals the weak Schur number WS(2) + 1.                                                                                               |
| 3   | F(3) = 54  | Reported first by [erdosproblemaday.com](https://erdosproblemaday.com/report/531) with an LRAT proof. We reproduced it independently. |
| 4   | F(4) ≥ 389 | This repository.                                                                                                                      |

Our reproduction of F(3) = 54 used our own encoder, `verify/cnf.py`. It writes one pair of clauses for each set: the subset sums are not all colour 0, and they are not all colour 1. It uses no symmetry breaking. CaDiCaL finds a colouring for N = 53, and its model was checked directly. CaDiCaL reports N = 54 unsatisfiable, drat-trim verifies its DRAT proof, and Kissat agrees. The same encoder gives F(2) = 9, with a drat-trim-verified proof for N = 9.

```sh
python3 verify/cnf.py 54 3 > n54.cnf
cadical n54.cnf n54.drat --no-binary
drat-trim n54.cnf n54.drat
```

## How the witness was found

The colourings were found by autonomous AI research agents. They used a SAT encoding with CaDiCaL and Kissat to reach N = 263. After that, min-conflicts local search with tabu, WalkSAT-style noise and large random perturbations (60 or more bits at once) extended each colouring to the next N, starting from the previous witness. Smaller perturbations stalled at N = 305. Several separately written checkers, in C and Python, confirmed the witnesses. They all ran on one machine, so they are independent implementations, not independent hardware.

As an independent re-verification, every witness produced by the agent chain, w200–w388 (141 files), was re-checked with a further separately written brute-force C verifier, `verify/f4_check.c`, which enumerates the same quadruple subset sums directly without any SAT dependency: every file reports `mono_cubes=0`. The full re-check log is kept at [validation.log](validation.log).

## Licence

The witness data is dedicated to the public domain under CC0 1.0. The checkers are released under the MIT licence.
