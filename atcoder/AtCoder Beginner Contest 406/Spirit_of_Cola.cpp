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
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, c1, c2, c3, w1, w2, w3;
int t, res = inf;
viii g, ans;
map<piii, int> ss;
bool dfs(int a, int b, int c) {
    if (ss.contains({a, b, c}) && ss[{a, b, c}] <= g.size()) return false;
    ss[{a, b, c}] = g.size();
    if (g.size() >= res) return false;
    g.pb(a, b, c);
    if (a == t || b == t || c == t) {
        if (g.size() < res) ans = g, res = g.size();
        g.pop_back();
        return false;
    }
    int u = inf;
    vi f = {a, b, c};
    rg::sort(f);
    int x = 0;
    while (x != 2 && f[x] == 0) x++;
    if (a == f[x]) dfs(0, b, c);
    if (b == f[x]) dfs(a, 0, c);
    if (c == f[x]) dfs(a, b, 0);
    int h = min(a, c2 - b);
    dfs(a - h, b + h, c);
    h = min(a, c3 - c);
    dfs(a - h, b, c + h);
    h = min(b, c1 - a);
    dfs(a + h, b - h, c);
    h = min(b, c3 - c);

    dfs(a, b - h, c + h);
    h = min(c, c1 - a);
    dfs(a + h, b, c - h);
    h = min(c, c2 - b);
    dfs(a, b + h, c - h);
    g.pop_back();
    return false;
}
void work() {
    cin >> c1 >> c2 >> c3;
    cin >> w1 >> w2 >> w3;
    cin >> t;
    dfs(w1, w2, w3);
    if (res != inf) {
        print(res - 1);
        for (int i = 1; i + 1 <= ans.size(); i++) {
            auto [u, v, p] = ans[i];
            print(u, v, p);
        }

    } else
        print(-1);
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