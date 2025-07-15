k, n = map(int, input().split())
f = set()
q = [(1, k, k*(k+1))]

# 改成有界循环

t=0
while n > 0:
    a,b,c=q[t]
    t+=1
    if k*(a+b)-c>0:
        q.append((a,b,k*(a+b)-c))
    if k*(b+c)-a>0:
        q.append((b,c,k*(b+c)-a))
    if k*(c+a)-b>0:
        q.append((c,a,k*(c+a)-b))
    if a in f or b in f or c  in f:
        continue
    for x in (a,b,c):
        f.add(x)
    print(a,b,c)
    n-=1
    