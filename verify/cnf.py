import sys, itertools
N=int(sys.argv[1]); k=int(sys.argv[2])
cl=set()
for A in itertools.combinations(range(1,N+1),k):
    if sum(A)>N: continue
    T=sorted({sum(c) for r in range(1,k+1) for c in itertools.combinations(A,r)})
    cl.add(tuple(T)); cl.add(tuple(-t for t in T))
print(f"p cnf {N} {len(cl)}")
for c in sorted(cl): print(*c,0)
