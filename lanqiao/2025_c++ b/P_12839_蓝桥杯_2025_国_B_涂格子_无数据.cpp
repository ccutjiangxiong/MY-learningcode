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
const int N = 2e6 + 5 , mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
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
vi e[N];

// ...existing code...
void work() {
    // read
    long long k;
    cin >> n >> m >> k;
    vector<tuple<long long, long long, int>> rec;
    rec.reserve(k);
    unordered_map<unsigned long long, int> mp;
    mp.reserve(k * 2);
    bool bad = false;
    for (int i = 0; i < k; i++) {
        long long x, y;
        int c;
        cin >> x >> y >> c;
        unsigned long long key = (x << 32) | y;
        if (mp.count(key)) {
            if (mp[key] != c) bad = true;
        } else
            mp[key] = c, rec.emplace_back(x, y, c);
    }
    if (bad) {
        cout << 0 << "\n";
        return;
    }
    // compress
    vector<long long> xs, ys;
    xs.reserve(rec.size());
    ys.reserve(rec.size());
    for (auto &t : rec) {
        xs.push_back(get<0>(t));
        ys.push_back(get<1>(t));
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int p = xs.size(), q = ys.size();
    // graph nodes 0..p-1 rows, p..p+q-1 cols
    vector<vector<pair<int, int>>> g(p + q);
    for (auto &t : rec) {
        int c = get<2>(t);
        int u = lower_bound(xs.begin(), xs.end(), get<0>(t)) - xs.begin();
        int v = lower_bound(ys.begin(), ys.end(), get<1>(t)) - ys.begin() + p;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    const int MOD = 998244353;
    auto mod_pow = [&](long long a, long long e) {
        long long r = 1;
        a %= MOD;
        while (e > 0) {
            if (e & 1) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    };
    long long sum_rc = 0;
    for (int O = 0; O < 2; O++) {
        vector<char> vis(p + q, 0), lab(p + q, 0);
        bool conflict = false;
        int comps = 0;
        for (int i = 0; i < p + q && !conflict; i++) {
            if (vis[i]) continue;
            comps++;
            queue<int> q0;
            vis[i] = 1;
            lab[i] = 0;
            q0.push(i);
            while (!q0.empty() && !conflict) {
                int u = q0.front();
                q0.pop();
                for (auto &e : g[u]) {
                    int v = e.first, w = e.second ^ O;
                    char want = lab[u] ^ w;
                    if (!vis[v]) {
                        vis[v] = 1;
                        lab[v] = want;
                        q0.push(v);
                    } else if (lab[v] != want) {
                        conflict = true;
                        break;
                    }
                }
            }
        }
        if (!conflict) {
            sum_rc = (sum_rc + mod_pow(2, comps)) % MOD;
        }
    }
    if (sum_rc == 0) {
        cout << 0 << "\n";
        return;
    }
    // free cuts
    long long e1 = ((n - 1 - p) % (MOD - 1) + (MOD - 1)) % (MOD - 1);
    long long e2 = ((m - 1 - q) % (MOD - 1) + (MOD - 1)) % (MOD - 1);
    long long free_cut = mod_pow(2, e1 + e2);
    cout << sum_rc * free_cut % MOD << "\n";
}
// ...existing code...
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}