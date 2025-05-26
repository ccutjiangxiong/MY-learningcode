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
#define sz(a) (int)a.size()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
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
const int N = 2e6 + 5, mod = 998244353, inf = 1e18 + 3;
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

int ti;
int n;
int a[N], b[N];
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}
void work() {
    cin >> n;
    n++;
    int ans = 0;
    int l = 0;
    rem(i, 63, 1) {
        if (n & (1ll << (i - 1ll))) (ans += a[i - 1] * b[l++]) %= mod;
    }
    print(ans);
}

signed main() {
    // a[0] = b[0] = 1;
    rep(i, 0, 63) a[i] = qpow(3, i, mod), b[i] = qpow(2, i, mod);
    // rep(i, 1, 10) print(a[i]);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}