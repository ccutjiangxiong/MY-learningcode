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
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];

int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}

void dfs(int u, int fa, int &x) {
    x++;
    for (int v : e[u])
        if (v != fa) {
            if (sz(e[u]) >= (3 - (u == 1))) {
                dfs(v, u, y);
                break;
            }
            dfs(v, u, x);
        }
}
void work() {
    cin >> n;
    rep(i, 1, n) e[i].clear();
    rep(i, 1, n - 1) be(e);
    cnt = 0;
    rep(i, 1, n) if (sz(e[i]) >= (3 - (i == 1))) cnt += sz(e[i]) - (2 - (i == 1));
    if (cnt > 1) {
        pt(0);
        return;
    }
    x = y = z = 0;
    dfs(1, 0, x);
    z = n - x - y;
    if (y < z) swap(z, y);
    int t = y - z;
    int a1 = 2;
    if (z != y) a1 = (qpow(2, t, mod) + qpow(2, t - 1, mod)) % mod;
    pt((qpow(2, x, mod) * (y ? a1 : 1)) % mod);
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