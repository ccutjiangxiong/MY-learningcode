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
const int N = 1e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
int ga[N], gb[N];
set<pii> ss;
void add(auto &t, int i, int p, int q) { t.ep(abs(a[i] - p), q * (p < a[i] ? -1 : 1)); }
void pre() {
    rep(i, 1, n) ss.ep(a[i], i);
    rep(i, 1, n) {
        auto u = ss.find({a[i], i});
        set<pii> s1, s2;
        if (u != ss.begin()) {
            auto [p, q] = *(--u);

            add(s1, i, p, q);
            add(s2, i, p, q);
            if (u != ss.begin()) {
                auto [p, q] = *(--u);
                add(s2, i, p, q);
            }
        }
        u = ss.find({a[i], i});
        if ((++u) != ss.end()) {
            auto [p, q] = *u;
            add(s1, i, p, q);
            add(s2, i, p, q);
            if ((++u) != ss.end()) {
                auto [p, q] = *u;
                add(s2, i, p, q);
            }
        }
        if (sz(s1)) gb[i] = abs((*s1.begin()).se);
        if (sz(s2) >= 2) ga[i] = abs((*(++s2.begin())).se);
        ss.erase({a[i], i});
    }
}
int f[55][N][2], da[55][N][2], db[55][N][2];
void fun() {
    rep(i, 1, n) {
        f[0][i][0] = ga[i], f[0][i][1] = gb[i];
        if (ga[i]) da[0][i][0] = abs(a[i] - a[ga[i]]);
        if (gb[i]) db[0][i][1] = abs(a[i] - a[gb[i]]);
    }
    rep(i, 1, 33) rep(j, 1, n) rep(k, 0, 1) {
        if (f[i - 1][j][k]) {
            f[i][j][k] = f[i - 1][(f[i - 1][j][k])][k ^ (i == 1)];
        }
        if (f[i][j][k]) da[i][j][k] = da[i - 1][j][k] + da[i - 1][(f[i - 1][j][k])][k ^ (i == 1)];
        if (f[i][j][k]) db[i][j][k] = db[i - 1][j][k] + db[i - 1][(f[i - 1][j][k])][k ^ (i == 1)];
    }
}
int la = 0, lb = 0;
void calc(int s, int x) {
    int sum = 0, ans = 0, k = 0;
    la = lb = 0;
    rem(i, 33, 0) {
        if (f[i][s][k]) {
            int su = da[i][s][k] + db[i][s][k];
            if (su <= x) x -= su, la += da[i][s][k], lb += db[i][s][k], s = f[i][s][k];
        }
    }
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int x, q;
    cin >> x >> q;
    pre(), fun();
    calc(1, x);
    int t = 1;
    ld e = inf;
    if (lb != 0) e = la * 1.0 / lb;
    rep(i, 2, n) {
        calc(i, x);
        ld x = inf;
        if (lb != 0) x = la * 1.0 / lb;
        if (x == e) t = (a[i] > a[t]) ? i : t;
        if (x < e) e = x, t = i;
    }
    print(t);
    rep(i, 1, q) {
        int s, x;
        cin >> s >> x;
        calc(s, x);
        print(la, lb);
    }
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