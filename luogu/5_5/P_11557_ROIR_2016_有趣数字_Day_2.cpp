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

int ti = 1;
string l, r;
int f[N][10];
int dp[111][22][22];
void pre() {}
int dfs(int p, int t, int la, string &s) {
    if (p == s.size()) return 1;
    if (dp[p][t][la]) return dp[p][t][la];
    int u = t ? (s[p] - '0') : 9;
    int res = 0;
    for (int d = la; d <= u; d++) (res += dfs(p + 1, t && (d == u), d, s)) %= mod;
    return dp[p][t][la] = res;
}
void work() {
    cin >> l >> r;
    int x = dfs(0, 1, 0, r);
    int f = 1;
    for (int i = 1; i + 1 <= l.size(); i++)
        if (l[i] < l[i - 1]) f = 0;
    me(dp, 0);
    cout << (x + mod + f - dfs(0, 1, 0, l)) % mod;
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