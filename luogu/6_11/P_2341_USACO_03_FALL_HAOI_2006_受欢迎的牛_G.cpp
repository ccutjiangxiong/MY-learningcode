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

int ti=1 ,n,m,k,a[N],b[N],c[N],ans,res,tot,x,y,z;
vi e[N];

void work() {
    cin >> n >> m;
    vector<vector<int>> g(n + 1), gr(n + 1);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u].pb(v);
        gr[v].pb(u);
    }

    vector<bool> vis(n + 1, false);
    vector<int> ord;
    function<void(int)> dfs1 = [&](int u) {
        vis[u] = true;
        for (int v : g[u])
            if (!vis[v]) dfs1(v);
        ord.pb(u);
    };
    rep(i, 1, n) if (!vis[i]) dfs1(i);

    vector<int> comp(n + 1, -1);
    int cid = 0;
    function<void(int)> dfs2 = [&](int u) {
        comp[u] = cid;
        for (int v : gr[u])
            if (comp[v] == -1) dfs2(v);
    };
    for (int i = (int)ord.size() - 1; i >= 0; i--) {
        int u = ord[i];
        if (comp[u] == -1) {
            dfs2(u);
            cid++;
        }
    }

    vector<int> szComp(cid, 0);
    rep(i, 1, n) szComp[comp[i]]++;

    vector<char> hasOut(cid, 0);
    rep(u, 1, n) {
        for (int v : g[u])
            if (comp[u] != comp[v]) hasOut[comp[u]] = 1;
    }

    int cnt = 0, pos = -1;
    rep(i, 0, cid - 1) {
        if (!hasOut[i]) {
            cnt++;
            pos = i;
        }
    }

    if (cnt == 1)
        pt(szComp[pos]);
    else
        pt(0);
}


    signed
    main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}