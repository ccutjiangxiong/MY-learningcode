#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define allp(a) a->begin(), a->end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define low lower_bound
#define upp upper_bound
#define con contains
#define me(a, x) memset(a, x, sizeof(a))
#define pta(x,a,b) rep(i,a,b) cout<<x[i]<<" \n"[i==b];
#define me1(x, n, ...) \
    for (auto *h : {__VA_ARGS__}) rep(i, 0, (n)) h[i] = x;
#define me2(x, n, m, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, 0, (n)) rep(j, 0, (m)) h[i][j] = x;
#define fi1(x, n1, n2, ...) \
    for (auto *h : {__VA_ARGS__}) rep(i, (n1), (n2)) h[i] = x;
#define fl2(x, n1, n2, m1, m2, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, (n1), (n2)) rep(j, (m1), (m2)) h[i][j] = x;
#define Ye(x) (x) ? "YES" : "NO"
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename Compare = std::greater<T>>
using hp = __gnu_pbds::priority_queue<T, Compare, pairing_heap_tag>;
template <typename Key, typename Mapped = null_type, typename Access = trie_string_access_traits<>>
using tri = trie<Key, Mapped, Access, pat_trie_tag, trie_prefix_search_node_update>;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;
using ll = int64_t;
using cpx = complex<ld>;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
int  s, t, mxf, mic, cnt;
vector<piii> e[N];
int g[N], dis[N], vis[N], pre[N], pe[N];
void add(int u, int v, int c, int w) {
    int x = cnt++, y = cnt++;
    e[u].pb(v, w, x);
    e[v].pb(u, -w, y);
    g[x] = c, g[y] = 0;
}
bool spfa(int s, int t) {
    rep(i,s,t) dis[i]=inf;
    queue<int> q;
    dis[s] = 0, vis[s] = 1, q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w, id] : e[u])
            if (g[id] && dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pre[v] = u, pe[v] = id;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
    }
    return dis[t] < inf;
}
void mcmf(int s, int t) {
    while (spfa(s, t)) {
        int fl = inf;
        for (int u = t; u != s; u = pre[u]) fl = min(fl, g[pe[u]]);
        mxf += fl, mic += fl * dis[t];
        for (int u = t; u != s; u = pre[u]) g[pe[u]] -= fl, g[pe[u] ^ 1] += fl;
    }
}

    // filepath: [P_1500_集训队互测_2000_丘比特的烦恼.cpp](http://_vscodecontentref_/4)
    void
    work() {
    ll k;
    cin >> k >> n;
    // read positions + map names → indices 1..2n
    vector<pair<ll, ll>> pos(2 * n + 1);
    unordered_map<string, int> id;
    string name;
    ll x, y;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y >> name;
        pos[i] = {x, y};
        id[name] = i;
    }
    for (int j = 1; j <= n; j++) {
        cin >> x >> y >> name;
        pos[n + j] = {x, y};
        id[name] = n + j;
    }
    // default affinity =1, override by input
    vector<vector<ll>> w(n + 1, vector<ll>(n + 1, 1));
    string n1, n2;
    ll p;
    while (cin >> n1) {
        if (n1 == "End") break;
        cin >> n2 >> p;
        int u = id[n1], v = id[n2];
        if (u <= n && v > n)
            w[u][v - n] = p;
        else if (v <= n && u > n)
            w[v][u - n] = p;
    }
    // build graph
    s = 0;
    t = 2 * n + 1;
    mxf = mic = 0;
    cnt = 0;
    for (int i = 0; i <= t; i++) e[i].clear();
    // source→men
    for (int i = 1; i <= n; i++) add(s, i, 1, 0);
    // women→sink
    for (int j = 1; j <= n; j++) add(n + j, t, 1, 0);
    ll kk = k * k;
    // men→women edges
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = i, v = n + j;
            ll dx = pos[u].first - pos[v].first;
            ll dy = pos[u].second - pos[v].second;
            if (dx * dx + dy * dy > kk) continue;
            bool ok = true;
            // check blocking
            for (int z = 1; z <= 2 * n; z++) {
                if (z == u || z == v) continue;
                ll x1 = pos[z].first - pos[u].first;
                ll y1 = pos[z].second - pos[u].second;
                ll x2 = pos[v].first - pos[u].first;
                ll y2 = pos[v].second - pos[u].second;
                if (x1 * y2 - x2 * y1 == 0) {
                    // collinear: check if z in [u,v]
                    ll dot =
                        x1 * (pos[z].first - pos[v].first) + y1 * (pos[z].second - pos[v].second);
                    if (dot <= 0) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) add(u, v, 1, -w[i][j]);
        }
    }
    mcmf(s, t);
    // mic is min‐cost = negative of total affinity
    cout << -mic << "\n";
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