#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int  N = 2e6 + 5,mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T> void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti=1;
// int n, q;
int c[N],s[N],t[N];
vector<int> e[N];
// vector<int> e[N];
vector<pii> que[N];
int fa[N], vis[N], ans[N], f[N][33];
int n, q, rt;
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
void tarjan(int u) {
  vis[u] = 1;
  for (int v : e[u])
    if (!vis[v])
      tarjan(v), fa[v] = u;
  for (auto &p : que[u]) {
    int v = p.first, i = p.second;
    if (vis[v])
      ans[i] = find(v);
  }
}
int dep[N], son[N], sz[N];
int top[N];
int id[N], nw[N];
void dfs1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1;
  for (int v : e[u])
    if (v ^ f) {
      dfs1(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[son[u]])
        son[u] = v;
    }
}
void dfs2(int u, int t) {
  top[u] = t;
  if (!son[u])
    return;
  dfs2(son[u], t);
  for (int v : e[u])
    if (v != fa[u] && v != son[u])
      dfs2(v, v);
}
int solve(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] <= dep[top[v]])
      swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}
void pre(int u, int fa) {
  dep[u] = dep[fa] + 1;
  f[u][0] = fa;
  rep(i, 1, 22) f[u][i] = f[f[u][i - 1]][i - 1];
  for (int v : e[u])
    if (v != fa)
      pre(v, u);
}
int lca(int u, int v) {
  if (dep[u] < dep[v])
    swap(u, v);
  rem(i, 22, 0) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
  if (u == v)
    return v;
  rem(i, 22, 0) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
  return f[u][0];
}
void work() {
    cin >> n >> q;
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    rt = 1;
    dfs1(1, 0);
    dfs2(1,0);
    rep(i, 1, q) cin >> s[i] >> t[i];
    rep(i, 1, q) {
        
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}