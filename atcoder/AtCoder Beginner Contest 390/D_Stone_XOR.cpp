#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define lbt(a) __builtin_ctz(a);
#define se second
#define fr first
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

int ti = 1, n, a[N];
unordered_set<int> ss, tt;
int vis[N], cnt = 0;
map<piii, int> mp;
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int full = (1 << n) - 1;

    vector<unordered_set<int>> dp(1 << n);
    dp[0].insert(0);

    vector<int> sum(1 << n, 0);
    for (int mask = 1; mask <= full; ++mask) {
        int i = lbt(mask);
        sum[mask] = sum[mask ^ (1 << i)] + a[i + 1];
    }
    for (int mask = 0; mask < full; ++mask) {
        int rem = full ^ mask;
        for (int sub = rem; sub; sub = (sub - 1) & rem) {
            int s = sum[sub];
            for (int x : dp[mask]) {
                dp[mask | sub].insert(x ^ s);
            }
        }
    }
    print(dp[full].size());
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