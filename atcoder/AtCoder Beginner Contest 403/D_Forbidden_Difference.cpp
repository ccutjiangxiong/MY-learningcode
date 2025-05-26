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

int ti = 1, n, d;
int a[N], h[N], vis[N];
vi b;
int dp[N][2];
int fun() {
    int l = b.size();
    rep(i, 1, l) {
        dp[i][1] = dp[i - 1][0] + b[i - 1];
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
    }
    return max(dp[l][0], dp[l][1]);
}
void work() {
    cin >> n >> d;
    rep(i, 1, n) cin >> a[i], h[a[i]]++;
    sort(a + 1, a + 1 + n);
    int ans = 0;
    rep(i, 0, a[n]) {
        int x = i;
        if (vis[x]) continue;
        while (h[x]) b.pb(h[x]), vis[x] = 1, x += d;
        ans += fun();
        b.clear();
    }
    print(n - ans);
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