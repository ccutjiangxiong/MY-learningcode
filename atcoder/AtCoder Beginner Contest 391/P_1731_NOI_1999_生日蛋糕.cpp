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

int ti = 1, n, m;
int ans = inf;
map<int, int> mp;
int pre[N], pre2[N];
void dfs(int u, int s, int lr, int lh, int v) {
    if (u == m && s == n) ans = min(ans, v);
    if (u == m || n - s < pre[m - u] || v + pre2[m - u] >= ans) return;
    rem(r, lr - 1, m - u) rem(h, lh - 1, m - u)
        dfs(u + 1, s + r * r * h, r, h, v + 2 * r * h + (u == 0 ? r * r : 0));
}
void work() {
    cin >> n >> m;
    rep(i, 1, m) pre[i] = pre[i - 1] + i * i * i, pre2[i] = pre2[i - 1] + 2 * i * i;
    dfs(0, 0, sqrt(n) + 1, n + 1, 0);
    print(ans == inf ? 0 : ans);
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