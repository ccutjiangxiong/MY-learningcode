#include <bits/stdc++.h>

#include <functional>

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
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti, n, a[N];
set<int> h[N];
set<int> e[N];
vi vis(N + 1);
void work() {
    cin >> n;
    rep(i, 1, N - 1) h[i].clear(), e[i].clear();
    vis.clear();
    rep(i, 1, n) cin >> a[i], h[a[i]].insert(i);
    rep(i, 1, N-1) {
        for (int u : h[i])
            for (int v : h[i + 1]) e[u].insert(v), e[v].insert(u);
    }

    int cnt = 0;
    function<void(int, int)> dfs = [&](int x, int fa) {
        vis[x] = 1;
        for (int v : e[x])
            if (v != fa&&!vis[v]) dfs(v, x);
    };
    rep(i, 1, n) if (!vis[i]) dfs(i, 0), cnt++;
    print(cnt - 1);
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