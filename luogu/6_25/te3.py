import sys

s = sys.stdin.readline().strip()
n = len(s)
f=[0]*n
g=[0]*n
for i in range(n):
    f[i]=int(s[0:i+1])
    g[i]=-1
    # print(i,f[i])
    # print(f[i])
for i in range(n):
    for j in range(i):
        t=int(s[j+1:i+1])
        # print(i,j,f[j],f[i],t)
        if t>f[j] and t<f[i]:

            f[i]=t
            g[i]=j
p=n-1
l=[-1]
while p>=0:
    l.append(p)
    p=g[p]
l.sort()
t=[]
for i in range(1,len(l)):
    x=l[i-1]+1
    y=l[i]
    t.append(s[x:y+1])
for i in range(len(t)-3, -1, -1):
    x = t[i]
    y = t[i+1]
    if int(x+y) < int(t[i+2]):
        t[i]   = x+y
        t[i+1] = t[i+2]
if len(t)==2:
    if int(t[0])==0:
        t=[t[0]+t[1]]
st=[]
for i in range(len(t)):
    if i==0 or t[i]!=t[i-1]:
        st.append(t[i])
for i in range(1,len(st)):
    while st[i][0]=='0' and int(st[i-1]+'0')<int(st[i][1:len(st[i])]):
        st[i-1]+='0'
        st[i]=st[i][1:len(st[i])]
for i in range(len(st)):
        print(st[i],end=' ' if i==len(st)-1 else ',')
