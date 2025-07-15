#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
vii e[N];
int g[N], d[N], cur[N], f[N];
int s, t, cnt = 0;
void add(int u, int v, int c, int id = 0) {
    int x = cnt++, y = cnt++;
    e[u].pb(v, x);
    e[v].pb(u, y);
    g[x] = c, g[y] = 0, f[id] = x;
}
bool bfs(int s, int t) {
    rep(i, s, t) d[i] = inf;
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : e[u]) {
            if (g[w] && d[v] == inf) {
                q.push(v);
                d[v] = d[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}
int dfs(int u, int flow, int t) {
    if (u == t) return flow;
    int sum = 0;
    for (int &i = cur[u]; i < e[u].size(); i++) {
        auto [v, w] = e[u][i];
        if (d[v] == d[u] + 1 && g[w]) {
            int f = min(flow, g[w]);
            int re = dfs(v, f, t);
            g[w] -= re, g[w ^ 1] += re;
            sum += re, flow -= re;
            if (flow == 0) break;
        }
    }
    if (sum == 0) d[u] = 0;
    return sum;
}
int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        ans += dfs(s, inf, t);
        me(cur, 0);
    }
    return ans;
}
int h[222][222];
bool cal(int x) {
    int y = a[x];
    int s = 0, t = n + n * n + 1;
    rep(i, 1, n) y += h[x][i];
    rep(i, 1, n) if (i != x && a[i] > y) return false;
    cnt = 0;
    rep(i, s, t) e[i].clear();
    rep(i, 1, n) rep(j, i + 1, n) if (i != x && j != x) {
        int id = (i - 1) * n + j;
        add(s, id, h[i][j]);
        add(id, n * n + i, inf);
        add(id, n * n + j, inf);
    }
    rep(i, 1, n) if (i != x) add(n * n + i, t, y - a[i]);
    return dinic(s, t) == (tot - y + a[x]);
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i] >> b[i];
    rep(i, 1, n) rep(j, 1, n) cin >> h[i][j];
    rep(i, 1, n) rep(j, i + 1, n) tot += h[i][j];
    rep(i, 1, n) if (cal(i)) cout << i << ' ';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}