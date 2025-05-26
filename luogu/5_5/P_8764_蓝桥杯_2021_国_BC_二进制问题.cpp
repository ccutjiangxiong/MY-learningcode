#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
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

int ti = 1, n, k, dp[111][111][2], a[N], len;
int dfs(int p, int t, int cnt) {
    if (dp[p][cnt][t] != -1) return dp[p][cnt][t];
    if (p > len) return cnt == k;
    int u = t ? a[p] : 1;
    int res = 0;
    rep(i, 0, u) res += dfs(p + 1, t && (i == a[p]), cnt + i);
    return dp[p][cnt][t] = res;
}
void work() {
    cin >> n >> k;
    len = log2(n);
    me(dp, -1);
    rep(i, 0, len) a[i] = (n >> i) & 1;
    reverse(a, a + len + 1);
    print(dfs(0, 1, 0));
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