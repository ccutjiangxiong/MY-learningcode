import sympy
t=int(input())
for _ in range(t):
    n,m=map(int,input().split())
    n=int(str(n)*m)
    if sympy.isprime(n):
        print("YES")
    else:
        print("NO")
