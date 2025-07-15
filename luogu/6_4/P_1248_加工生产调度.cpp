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
#define gt(f, a) get<a>(f)
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
piii f[N];
bool jud(piii &a, piii &b) {
    auto [a1, b1, i1] = a;
    auto [a2, b2, i2] = b;
    // if (a1 < b1 && a2 < b2) return a1 < a2;
    // if (a1 > b1 && a2 > b2) return b1 > b2;
    return min(a1, b2) < min(a2, b1);
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> gt(f[i], 0);
    rep(i, 1, n) cin >> gt(f[i], 1);
    rep(i, 1, n) gt(f[i], 2) = i;
    res = inf;
    vi ans;
    rep(i, 1, 100) {
        shuffle(f + 1, f + 1 + n, rng);
        sort(f + 1, f + 1 + n, jud);
        x = gt(f[1], 0), y = gt(f[1], 1) + x;
        rep(i, 2, n) y = max(x + gt(f[i], 0), y) + gt(f[i], 1), x += gt(f[i], 0);
        if (y < res) {
            ans.clear();
            rep(i, 1, n) ans.pb(get<2>(f[i]));
            res = y;
        }
    }
    print(res);
    for (int v : ans) cout << v << ' ';
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