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
vi e[N];
void work() {
    cin >> n;
    set<int> ans, tt;
    rep(i, 1, n) cin >> a[i], tt.ep(a[i]);
    rep(i, 1, n) b[a[i]]++;
    set<pii> s;
    rep(i, 1, 1e6) if (b[i]) s.ep(b[i], i);
    vi g;
    for (int u : tt) g.pb(u);
    for (int u : g)
        for (int v : g) {
            if (u == v && b[u] == 1) continue;
            set<pii> s1, s2;
            s1.ep(b[u], u), s1.ep(b[u + 1], u + 1), s1.ep(b[v], v), s1.ep(b[v - 1], v - 1);
            s2.ep(b[u + 1] + 1, u + 1), s2.ep(b[u] - 1, u), s2.ep(b[v] - 1, v),
                s2.ep(b[v - 1] + 1, v - 1);
            for (auto x : s1) s.erase(x);
            for (auto x : s2) s.ep(x);
            ans.ep(s.rbegin()->se);
            for (auto x : s2) s.erase(x);
            for (auto x : s1) s.ep(x);
        }
    for (auto v : ans) cout << v << ' ';
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