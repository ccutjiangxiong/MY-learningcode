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
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vii e[N];
int f[N][44], d[N][44];
void dfs(int u, int fa) {
    rep(i, 1, 33) f[u][i] = f[(f[u][i - 1])][i - 1];
    rep(i, 1, 33) d[u][i] = d[u][i - 1] + d[(f[u][i - 1])][i - 1];

    for (auto [v, w] : e[u])
        if (fa != v) f[v][0] = u, d[v][0] = w, dfs(v, u);
}
vi g;
set<pii> h;
void fun1(int t) {
    rep(i, 1, m) {
        int x = t, s = a[i];
        rem(j, 33, 0) {
            if (f[s][j] >= 2 && x >= d[s][j]) x -= d[s][j], s = f[s][j];
        }
        if (f[s][0] == 1 && x >= d[s][0])
            h.ep(s, x);
        else
            b[s]++;

    }
}

bool dfs1(int u, int fa) {
    if (b[u]) return true;
    if (u != 1 && e[u].size() == 1) return false;

    for (auto [v, w] : e[u])
        if (v != fa) {
            // print(u,v);
            if (dfs1(v, u)) return true;
            if (u != 1) return false;
            if (u == 1) {
                auto it = h.lower_bound({v, 0});
                if (it != h.end() && it->fi == v)
                    h.erase(it);
                else
                    g.pb(w);
            } 
        }
    return true;
}
bool check(int t) {
    rep(i, 1, n) b[i] = 0;
    g.clear(), h.clear();
    fun1(t);
    dfs1(1, 0);
    vi rg;
    for (auto [v, t] : h)
        if (t >= d[v][0]) rg.pb(t - d[v][0]);
    rg::sort(g);
    rg::sort(rg);
    while (g.size()) {
        if (rg.empty() || g.back() > rg.back()) return false;
        g.pop_back();
        rg.pop_back();
    }
    return true;
}

void work() {
    cin >> n;
    rep(i, 1, n - 1) {
        cin >> x >> y >> z;
        e[x].pb(y, z);
        e[y].pb(x, z);
    }
    cin >> m;
    rep(i, 1, m) cin >> a[i];
    dfs(1, 0);
    int l = 0, r = inf;

    while (l <= r) {
        int mid = (l + r) >> 1;

        if (check(mid))

            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    print(ans != inf ? ans : -1);
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