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
const int N = 100 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
vi e[N];
int slk[N], pre[N], vis[N], mch[N], lx[N], ly[N], C[2222][2222];
void bfs(int k) {
    int px, py = 0, yy = 0, d;
    me(pre, 0), me(slk, 0x3f);
    mch[py] = k;
    while (true) {
        px = mch[py], d = inf, vis[py] = 1;
        rep(i, 1, n) if (vis[i] == 0) {
            if (slk[i] > lx[px] + ly[i] - C[px][i]) slk[i] = lx[px] + ly[i] - C[px][i], pre[i] = py;
            if (slk[i] < d) d = slk[i], yy = i;
        }
        rep(i, 0, n) if (vis[i]) lx[mch[i]] -= d, ly[i] += d;
        else slk[i] -= d;
        if (mch[py = yy] == 0) break;
    }
    while (py) mch[py] = mch[pre[py]], py = pre[py];
}
int km() {
    me(lx, 0), me(ly, 0), me(mch, 0);
    rep(i, 1, n) me(vis, 0), bfs(i);
    rep(i, 1, n) if (vis[i]) vis[0] += C[mch[i]][i];
    return vis[0];
}
void work() {
    cin >> n;
    rep(i, 1, n) rep(j, 1, n) cin >> C[i][j];
    set<pii> s;
    ans = km();
    vii g;
    rep(i, 1, n) g.pb(mch[i], i);
    for (auto [i, j] : g) {
        x = C[i][j];
        C[i][j] = -inf;
        y = km();
        if (ans > y) s.ep(i, j);
        C[i][j] = x;
    }
    pt(ans);
    for (auto [x, y] : s) pt(x, y);
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