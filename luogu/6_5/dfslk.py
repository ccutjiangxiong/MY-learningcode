n=int(input())
ans=1
cnt=2
g=[]

if(n==8):
    print(3,5)
    print(15)
    exit()
while n:   
    if n>=cnt:
         n-=cnt
         g.append(cnt)
         cnt=cnt+1
    else :
        t=cnt-n
        if t==1:
            g[-1]+=n
        else:
            g[g.index(t)] += n
        n=0
g.sort()
for x in g:
     print(x,end=' ')
     ans*=x
print()
print(ans)
