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
int judge(int k) {
    rep(i, 1, n) {
        b[i] = b[i - 1] + a[i];
        if (i - k - 1 >= 0) b[i] = min(b[i], b[i - k - 1] + c[i - 1] - c[i - k - 1]);
    }
    // pt(k, b[n]);
    return b[n] <= m;
}
void work() {
    cin >> n >> m;
    rep(i, 1, n + 1) a[i] = b[i] = c[i] = 0;
    rep(i, 1, n) cin >> a[i], c[i] = c[i - 1] + a[i];
    if (c[n] <= m) {
        pt(-1);
        return;
    };
    int ans = 0, l = 0, r = n;
    // judge(2);
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (judge(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    pt(ans ? ans + 1 : -1);
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