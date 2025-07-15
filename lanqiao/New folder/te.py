import math
a=10120300500*2;
ans=0
mp = set()
for i   in range(1,a+1):
    if i*i >a:
        break
    if(a%i==0):
        u=a//i;
        v=i
        if (u-v)%2==0:
            mp.add((u*u+v*v)//4);
for x in mp:
    ans+=x
print(ans)
