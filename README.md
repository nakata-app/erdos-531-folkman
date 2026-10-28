# Erdős Problem #531: a lower bound F(4) ≥ 397

## The problem

From [erdosproblems.com/531](https://www.erdosproblems.com/531):

> Let $F(k)$ be the minimal $N$ such that if we two-colour $\{1,\ldots,N\}$ there is a set $A$ of size $k$ such that all subset sums $\sum_{a\in S}a$ (for $\emptyset\neq S\subseteq A$) are monochromatic. Estimate $F(k)$.

A colour is only defined on {1, …, N}, so a set A counts only when sum(A) ≤ N. The elements of A are distinct.

## The result

`witnesses/w396.txt` is a 2-colouring of {1, …, 396}. Character i (counting from 1) is the colour of the integer i. No set {a < b < c < d} with a + b + c + d ≤ 396 has all 15 nonempty subset sums the same colour. Therefore

**F(4) ≥ 397.**

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
| `witnesses/w389.txt` | 389    | `08a14219e4f450bb6dff33e8202da1823b65338f39018fa883b6c2a490fcbecb` |
| `witnesses/w390.txt` | 390    | `d3b5103143bf21d852643f5c4283c952490d204124452d0f1c7193741545a1de` |
| `witnesses/w391.txt` | 391    | `830761d29dfe8a78439b59088691ebf24287f31c7877fe9b6b120f418d48e2a4` |
| `witnesses/w392.txt` | 392    | `47b8b7824382681010c703ff1027aebabc6651c17e2f6b611a9987c6e70f617a` |
| `witnesses/w393.txt` | 393    | `a5d51acc9542ce87643c6193e3a06a764d70402ed61e3c9323bf370832882ab2` |
| `witnesses/w394.txt` | 394    | `da609d657b3a861cdcca87d5a8af998515f7c59dc847250bb7df5e06019fc680` |
| `witnesses/w395.txt` | 395    | `f2043338048f07ca18a19147a881bfa30a7a603fde47e260caac09f344ffcf4f` |
| `witnesses/w396.txt` | 396    | `a0ca6789beb0fb831a914ad03a817d5b6e74d4a56a16d2788addba536a673c3d` |

As far as we could find, the best previously reported value was F(4) ≥ 201, in a working report on [erdosproblemaday.com](https://erdosproblemaday.com/problem/531) maintained by Patrick White. We found no value of F(4) on erdosproblems.com, in the OEIS, or in the published literature. Please open an issue if you know of one.

This is a lower bound only. It says nothing about the exact value of F(4). Showing that F(4) = N requires proving that every 2-colouring of {1, …, N} contains such a set, for example with a SAT solver and a checked unsatisfiability proof. We have not done that.

## Verify it yourself

The check is self-contained and takes about a second in C.

```sh
shasum -a 256 witnesses/w396.txt
cc -O2 -o check verify/check.c
./check witnesses/w396.txt
```

Expected output:

```
N=396 tested=40781268 mono=0
```

A dependency-free Python checker gives the same result more slowly:

```sh
python3 verify/check.py witnesses/w396.txt
```

Both checkers print the first monochromatic set they find and exit with status 1 if there is one. As a sanity check, an all-zero string of length 396 makes every set monochromatic: `tested=40781268 mono=40781268`.

## Small values

| k   | Value      | Status                                                                                                                                |
| --- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| 2   | F(2) = 9   | Equals the weak Schur number WS(2) + 1.                                                                                               |
| 3   | F(3) = 54  | Reported first by [erdosproblemaday.com](https://erdosproblemaday.com/report/531) with an LRAT proof. We reproduced it independently. |
| 4   | F(4) ≥ 397 | This repository.                                                                                                                      |

Our reproduction of F(3) = 54 used our own encoder, `verify/cnf.py`. It writes one pair of clauses for each set: the subset sums are not all colour 0, and they are not all colour 1. It uses no symmetry breaking. CaDiCaL finds a colouring for N = 53, and its model was checked directly. CaDiCaL reports N = 54 unsatisfiable, drat-trim verifies its DRAT proof, and Kissat agrees. The same encoder gives F(2) = 9, with a drat-trim-verified proof for N = 9.

```sh
python3 verify/cnf.py 54 3 > n54.cnf
cadical n54.cnf n54.drat --no-binary
drat-trim n54.cnf n54.drat
```

## How the witness was found

The colourings were found by autonomous AI research agents built on two language models: DeepSeek (DeepSeek-V4 family, driving the search agent that wrote and tuned the local-search code) and Claude (Anthropic, Claude Code, which wrote the verifiers, ran the independent re-checks and maintained this repository). Every witness was checked by programs, not by the models' own claims. They used a SAT encoding with CaDiCaL and Kissat to reach N = 263. After that, min-conflicts local search with tabu, WalkSAT-style noise and large random perturbations (60 or more bits at once) extended each colouring to the next N, starting from the previous witness. Smaller perturbations stalled at N = 305. Several separately written checkers, in C and Python, confirmed the witnesses. They all ran on one machine, so they are independent implementations, not independent hardware.

As an independent re-verification, every witness in this repository (26 files: w331, w372–w396) was re-checked on 2026-10-22 with the current `verify/f4_check.c` (after commit 31cde83 fixed its colour-1 initialisation), a separately written brute-force C verifier that enumerates the same quadruple subset sums directly without any SAT dependency: every file reports `mono_cubes=0`, see [validation.log](validation.log). The full local chain produced by the agents, w200–w396 (149 files, not all of them kept in this repository), was re-checked the same way: [validation-chain.log](validation-chain.log). Note on the witness format: each `wN.txt` is a single line of N characters with no trailing newline (w396.txt was fixed on 2026-10-22; its SHA-256 is now `2a57e17ea0bea652699a3149c5ac9c0ca71bdf77029b9f52a7fbb5c53ca11f2e`; the earlier 397-byte form with an embedded newline had SHA-256 `a0ca6789beb0fb831a914ad03a817d5b6e74d4a56a16d2788addba536a673c3d` and encodes the same colouring).

## Licence

The witness data is dedicated to the public domain under CC0 1.0. The checkers are released under the MIT licence.

## k = 5: a lower bound F(5) ≥ 1514 (work in progress)

`witnesses/k5_w1494.txt` is a 2-colouring of {1, …, 1494} (character i = colour of i). No 5-set {a<b<c<d<e} with
a+b+c+d+e ≤ 1494 has all 31 nonempty subset sums the same colour. The repair chain has since been extended to
`witnesses/k5_w1513.txt`, giving **F(5) ≥ 1514**. (The apparent stall at 1495 was not a wall: a heavier repair
budget — 15000 iterations per restart, abort over 1000 violations, up to 100 seeds — passed it on seed 335.) Earlier chain points:
`k5_w1400.txt` (F(5) ≥ 1401), `k5_w1451.txt` (F(5) ≥ 1452). The witnesses `k5_w1452` … `k5_w1494` were produced by
the repair mode of `k5_climb` (`fix N+1 3000 witnesses/k5_wN.txt seed 400`: short tabu-walk restarts from the
previous witness, a restart is abandoned when its violation count exceeds 400); every one of them passes
`verify/k5_check.c`. The from-scratch climb stalls near 1450; repair restarts pass such points (e.g. 1467 needed
16 restarts).

Checked by two independent programs: `verify/k5_dfs.py` (search-side) and `verify/k5_check.c` (written separately;
negative control: flipping one colour of the witness yields 7 monochromatic 5-sets, the all-zero colouring of
{1..20} yields 19). `verify/k5_brute.c` is a third, slower checker (not run to completion for n ≥ 1000).
Search: `search/k5_climb.c` (local search / hill climb, chain `witnesses/k5_w100 … k5_w1400`).

| Witness | Length | SHA-256 |
| --- | --- | --- |
| `witnesses/k5_w1513.txt` | 1513 | `b620e7c0c5f4de1d172a1952226b120c40bdddfe93279fe7842c9e4aaf7d6cc1` |
| `witnesses/k5_w1494.txt` | 1494 | `93d8657710a0b51d05db3171ba8322aa23ac3bfeaa175fe54f248f5347ea3929` |
| `witnesses/k5_w1451.txt` | 1451 | `0d94249f55bd414420ea1a6b4b545976ba25e7cc3bf771b5873b8a4ef1782377` |
| `witnesses/k5_w1400.txt` | 1400 | `c59b4673c4ce9a9428ac04c6808b09c094c0a87b85c224338700d059a30d9011` |

For comparison, the general bound of Balogh–Eberhard–Narayanan–Treglown–Wagner, F(k) ≥ 2^{2^{k-1}/k}, gives only
F(5) ≥ 10; no specific F(5) value is listed on erdosproblems.com/531. The chain is still climbing.
