# Erdős Problem #531: a lower bound F(4) ≥ 306

## The problem

Let F(k) be the least N such that every 2-colouring of {1, …, N} contains a set A of k distinct positive integers whose nonempty subset sums all have the same colour ([Erdős Problem #531](https://www.erdosproblems.com/531)). Every subset sum must lie in {1, …, N}, so only sets with sum(A) ≤ N count.

## The result

`witnesses/w305.txt` is a 2-colouring of {1, …, 305}. Character i (counting from 1) is the colour of the integer i. No set {a < b < c < d} with a + b + c + d ≤ 305 has all 15 nonempty subset sums the same colour. Therefore

**F(4) ≥ 306.**

| Witness | Length | SHA-256 |
|---|---|---|
| `witnesses/w305.txt` | 305 | `d85c6f85f385959e90c0fd86eae47d68e725e98539afeba1831a2704607aee0c` |

As far as we could find, the best previously reported value was F(4) ≥ 201, in a working report on [erdosproblemaday.com](https://erdosproblemaday.com/problem/531) maintained by Patrick White. We found no value of F(4) on erdosproblems.com, in the OEIS, or in the published literature. Please open an issue if you know of one.

This is a lower bound only. It says nothing about the exact value of F(4). Showing that F(4) = N requires proving that every 2-colouring of {1, …, N} contains such a set, for example with a SAT solver and a checked unsatisfiability proof. We have not done that.

## Verify it yourself

The check is self-contained and takes about a second in C.

```sh
shasum -a 256 witnesses/w305.txt
cc -O2 -o check verify/check.c
./check witnesses/w305.txt
```

Expected output:

```
N=305 tested=14154050 mono=0
```

A dependency-free Python checker gives the same result more slowly:

```sh
python3 verify/check.py witnesses/w305.txt
```

Both checkers print the first monochromatic set they find and exit with status 1 if there is one. As a sanity check, an all-zero string of length 305 makes every set monochromatic: `tested=14154050 mono=14154050`.

## How the witness was found

The colourings were found by autonomous AI research agents. They used a SAT encoding with CaDiCaL and Kissat to reach N = 263. After that, min-conflicts local search with tabu and random restarts extended each colouring to the next N, starting from the previous witness. Several separately written checkers, in C and Python, confirmed the witnesses. They all ran on one machine, so they are independent implementations, not independent hardware.

## Licence

The witness data is dedicated to the public domain under CC0 1.0. The checkers are released under the MIT licence.
