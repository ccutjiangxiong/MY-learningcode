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
int c[N];
vi h[N];
int ans = inf;
int vis[N];
void dfs(int x, int val) {
    if (x > n) return;
    int f = 1;
    rep(i, 1, m) if (vis[i] < 2) f = 0;
    if (f) ans = min(ans, val);
    dfs(x + 1, val);
    for (int y : h[x + 1]) vis[y]++;
    dfs(x + 1, val + c[x + 1]);
    for (int y : h[x + 1]) vis[y]--;
    for (int y : h[x + 1]) vis[y]+=2;
    dfs(x + 1, val + 2*c[x + 1]);
    for (int y : h[x + 1]) vis[y]-=2;
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, m) {
        int x;
        cin >> x;
        rep(j, 1, x) {
            int y;
            cin >> y;
            h[y].pb(i);
        }
    }
    dfs(0, 0);
    print(ans);
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