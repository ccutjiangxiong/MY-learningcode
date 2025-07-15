t=int(input())
for i in range(t):
    n,a=map(int,input().split())
    x = 1; [ x := x * i for i in range(1, n+1)]
    print(str(x).count(str(a)))
