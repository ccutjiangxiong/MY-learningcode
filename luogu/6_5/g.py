t=int(input())
for i in range(t):
    l,r=map(int,input().split())
    print((r-l+1)*(l+r)//2%9)