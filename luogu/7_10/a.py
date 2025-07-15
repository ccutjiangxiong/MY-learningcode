s=[[0]*500 for i in range(555)]
for i in range(500):
    s[i][i]=s[i][1]=1
    for j in range(2,i):
        s[i][j]=s[i-1][j-1]+j*s[i-1][j]
while 1:
    try:
        n,m=map(int,input().split())
        print(s[n][m])
    except EOFError:
        break
