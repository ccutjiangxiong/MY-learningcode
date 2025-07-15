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

int ti, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];

void work() {
    int p, s;
    cin >> p >> s;
    if (p == 4 * s)
        pt(1), pt(1, 1);
    else if (p == 2 * s) {
        pt(4);
        rep(i, 1, 2) rep(j, 1, 2) pt(i, j);
    } else if (p > 2 * s) {
        int y = p - 2 * s;
        x = (s * 2) / y - 1;
        if ((s * 2) % y == 0 && x >= 1) {
            pt(x + 1);
            rep(i, 1, x + 1) pt(1, i);
        } else
            pt(-1);
    } else {
        int l = 0;
        if (p & 1) {
            k = p / 2;
            s -= (p / 2);
            l = 4 * s;
        } else {
            k = p > 2 ? (p - 2) / 2 : 0;
            s -= k;
            l = 2 * s;
        }
        pt(l * l + k);
        rep(i, 1, l) rep(j, 1, l) pt(i, j);
        // rep(i, 0, k) pt(1, -i);
        rep(i,0,k-1) pt(1,-(i-1));
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