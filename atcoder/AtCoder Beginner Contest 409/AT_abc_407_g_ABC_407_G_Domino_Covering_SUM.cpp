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

int ti = 1, k, a[N], b[N], c[N], ans, res, x, y, z;
int gr[2222][2222];
int n, m, s, t, mxf, mic, cnt;
vector<piii> e[N];
int g[N], dis[N], vis[N], pre[N], pe[N];
void add(int u, int v, int c, int w) {
    int x = cnt++, y = cnt++;
    e[u].pb(v, w, x);
    e[v].pb(u, -w, y);
    g[x] = c, g[y] = 0;
}
bool spfa(int s, int t) {
    me(dis, 0x3f);
    queue<int> q;
    dis[s] = 0, vis[s] = 1, q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w, id] : e[u])
            if (g[id] && dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pre[v] = u, pe[v] = id;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
    }
    return dis[t] < inf;
}
void mcmf(int s, int t) {
    while (spfa(s, t) && dis[t] < 0) {
        int fl = inf;
        for (int u = t; u != s; u = pre[u]) fl = min(fl, g[pe[u]]);
        mxf += fl, mic += fl * dis[t];
        for (int u = t; u != s; u = pre[u]) g[pe[u]] -= fl, g[pe[u] ^ 1] += fl;
    }
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> gr[i][j], ans += gr[i][j];
    int t = n * m + 1, s = 0;
    rep(i, 1, n) rep(j, 1, m) {
        int id = (i - 1) * m + j;
        if ((i + j) & 1) {
            add(s, id, 1, 0);
            if (j < m && gr[i][j] + gr[i][j + 1] < 0) add(id, id + 1, 1, gr[i][j] + gr[i][j + 1]);
            if (i < n && gr[i][j] + gr[i + 1][j] < 0) add(id, id + m, 1, gr[i][j] + gr[i + 1][j]);
            if (j > 1 && gr[i][j] + gr[i][j - 1] < 0) add(id, id - 1, 1, gr[i][j] + gr[i][j - 1]);
            if (i > 1 && gr[i][j] + gr[i - 1][j] < 0) add(id, id - m, 1, gr[i][j] + gr[i - 1][j]);
        } else
            add(id, t, 1, 0);
    }
    mcmf(s, t);
    pt(ans - mic);
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