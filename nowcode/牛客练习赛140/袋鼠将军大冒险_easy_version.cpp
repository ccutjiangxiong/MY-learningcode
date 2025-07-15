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
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti,n,m,k,a[N],b[N],c[N],ans,res,cnt,x,y,z;
vi e[N];

void work() {
    int n;
    cin >> n;
    vector<int> supply(n + 1);
    for (int i = 1; i <= n; i++) cin >> supply[i];

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int q;
    cin >> q;  
    int s, t;
    cin >> s >> t;

    vector<int> par(n + 1, -1), pw(n + 1, 0);
    vector<vector<pair<int, int>>> child(n + 1);
    vector<int> stk;
    par[t] = 0;
    stk.push_back(t);
    for (int i = 0; i < (int)stk.size(); i++) {
        int u = stk[i];
        for (auto &ed : adj[u]) {
            int v = ed.first, w = ed.second;
            if (par[v] == -1) {
                par[v] = u;
                pw[v] = w;
                child[u].emplace_back(v, w);
                stk.push_back(v);
            }
        }
    }

    vector<int> s1, post;
    s1.push_back(t);
    while (!s1.empty()) {
        int u = s1.back();
        s1.pop_back();
        post.push_back(u);
        for (auto &ed : child[u]) s1.push_back(ed.first);
    }

    vector<int> f(n + 1, 0);
    for (int i = (int)post.size() - 1; i >= 0; i--) {
        int u = post[i];
        int sum = 0;
        for (auto &ed : child[u]) {
            int v = ed.first, w = ed.second;
            int c = f[v] + supply[v] - 2LL * w;
            if (c > 0) sum += c;
        }
        f[u] = sum;
    }

    vector<int> path;
    for (int u = s; u != 0; u = par[u]) {
        path.push_back(u);
        if (u == t) break;
    }

    int ss = 0, pc = 0, bs = 0;
    for (int i = 0; i < (int)path.size(); i++) {
        int u = path[i];
        ss += supply[u];
        if (i > 0) {
            int v = path[i - 1];
            pc += pw[v];
        }
        int gu = f[u];
        if (i > 0) {
            int v = path[i - 1];
            int c = f[v] + supply[v] - 2LL * pw[v];
            if (c > 0) gu -= c;
        }
        bs += gu;
    }

    int ans = ss + bs - pc;
    cout << ans << "\n";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}