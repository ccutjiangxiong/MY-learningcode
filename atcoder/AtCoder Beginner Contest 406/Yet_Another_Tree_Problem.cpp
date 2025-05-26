#include <bits/stdc++.h>

#include <algorithm>

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

int ti, n, s, pre[N], b[N], su[N], c[N];
ld fun(int i, int x, int y) {
    int h = su[n] - su[n - x] - y;
    int u = h / x, v = h - u * x;
    ld sum = pre[n - x] - pre[i] + u * u * x + v * (2 * u + 1);
    ld k = n - i, m = su[n] - s;
    ld res = sum / k - m * m / k / k;
    return res;
}
void work() {
    cin >> n >> s;
    rep(i, 1, n) cin >> b[i];
    sort(b + 1, b + 1 + n);
    rep(i, 1, n) su[i] = su[i - 1] + b[i], pre[i] = b[i] * b[i] + pre[i - 1];
    rep(i, 1, n) c[i] = su[n] - su[i] - (n - i) * b[i];
    reverse(c + 1, c + 1 + n);
    ld ans = inf;
    rep(i, 0, n) {
        int y = s - su[i];
        if (y < 0) break;
        int x = lower_bound(c + 1, c + 1 + n, y) - c;
        if(c[x]>y)x--;
        x = min(x, n - i);
        ans = min(ans, fun(i, x, y));
    }
    cout << format("{:.6f}", ans) << endl;
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