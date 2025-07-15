import sys
sys.setrecursionlimit(10**7)
input = sys.stdin.readline

n, k = map(int, input().split())

# f[a][b] = None 或 (num, exp)，代表 num / 2**exp
f = [[None]*(n+1) for _ in range(n+1)]
e = [[] for _ in range(n+1)]
fa = [[0,0] for _ in range(n+2)]
indeg = [0]*(n+1)

for _ in range(k):
    a,b,c = map(int, input().split())
    e[b].append(a)
    e[c].append(a)
    fa[a][0], fa[a][1] = b, c
    indeg[a] += 2

# 自己和自己相似度 = 1/1 = (1,0)
for i in range(1, n+1):
    f[i][i] = (1, 0)

# 拓扑排序计算层次 q[]
st, g, q = [], [], [0]*(n+1)
for i in range(1, n+1):
    if indeg[i] == 0:
        st.append(i)
while st:
    u = st.pop()
    g.append(u)
    for v in e[u]:
        indeg[v] -= 1
        if indeg[v] == 0:
            st.append(v)
for idx, u in enumerate(g, start=1):
    q[u] = idx

def dfs(a, b):
    if f[a][b] is not None:
        return f[a][b]
    # 保证 a 层次 >= b
    if q[a] < q[b]:
        a,b = b,a
    # 初代妖怪直接 0
    if fa[a][0] == 0:
        f[a][b] = f[b][a] = (0, 0)
        return (0, 0)
    n1,e1 = dfs(fa[a][0], b)
    n2,e2 = dfs(fa[a][1], b)
    # 对齐指数
    me = max(e1, e2)
    if e1 < me: n1 <<= (me - e1)
    if e2 < me: n2 <<= (me - e2)
    s = n1 + n2
    # 除以 2 -> exp+1
    res = (s, me+1)
    f[a][b] = f[b][a] = res
    return res

m = int(input())
out = []
for _ in range(m):
    a,b = map(int, input().split())
    num, exp = dfs(a, b)
    # 乘 100
    num100 = num * 100
    # 整数部分
    ip = num100 >> exp
    rem = num100 - (ip << exp)
    print(num100,ip,rem);
    if rem == 0:
        out.append(f"{ip}%")
    else:
        digs = []
        while rem:
            rem *= 10
            d = rem >> exp
            digs.append(str(d))
            rem -= (d << exp)
        # 去尾零
        while digs and digs[-1] == '0':
            digs.pop()
        out.append(f"{ip}." + "".join(digs) + "%")

sys.stdout.write("\n".join(out))