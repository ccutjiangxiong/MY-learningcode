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

int ti, n, m, k, a[N], ans, res, cnt, x, y, z;
int a1, a2;
void sa(int t) {
    uniform_int_distribution<int> dx(1, k), dy(k + 1, n);
    ld dt = 1.0 / n;
    rem(i, t, 1) {
        x = dx(rng), y = dy(rng);
        int na = a1 - a[x] + a[y], nb = a2 - a[y] + a[x];
        int ne = llabs(na - nb);

        if (ne < res || (ran(1, t)*1.5 < (dt * i))) a1 = na, a2 = nb, swap(a[x], a[y]), res = ne;
        ans = min({res, ne, ans});
    }
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    if (n == 1) {
        pt(a[1]);
        return;
    }
    if (n == 2) {
        pt(abs(a[2] - a[1]));
        return;
    }
    k = n / 2;
    a1 = 0, a2 = 0;
    rep(i, 1, k) a1 += a[i];
    rep(i, k + 1, n) a2 += a[i];
    ans = res = abs(a1 - a2);
    sa(10000);
    pt(ans);
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