import sys
sys.setrecursionlimit(10**7)
input = sys.stdin.readline

n = int(input())
adj = [[] for _ in range(n+1)]
for _ in range(n-1):
    u, v = map(int, input().split())
    adj[u].append(v)
    adj[v].append(u)

def dfs(u, fa):
    # f[t] = max product of all OTHER components in subtree(u)
    #       when the component containing u has size t
    f = [-1, 1]   # f[0] unused; f[1]=1 (leaf)
    sz = 1
    for v in adj[u]:
        if v == fa: continue
        f_v, sz_v = dfs(v, u)
        new_sz = sz + sz_v
        newf = [-1] * (new_sz + 1)
        for t1 in range(1, sz+1):
            if f[t1] < 0: continue
            for t2 in range(1, sz_v+1):
                if f_v[t2] < 0: continue
                # 1) cut edge u–v: v’s component gives factor t2 * f_v[t2]
                cut_val = f[t1] * (f_v[t2] * t2)
                if cut_val > newf[t1]:
                    newf[t1] = cut_val
                # 2) keep edge: merge v’s component into u’s -> size t1+t2
                keep_val = f[t1] * f_v[t2]
                idx = t1 + t2
                if keep_val > newf[idx]:
                    newf[idx] = keep_val
        f, sz = newf, new_sz
    return f, sz

f_root, _ = dfs(1, 0)
ans = max(f_root[t] * t for t in range(1, n+1) if f_root[t] >= 0)
print(ans)