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
#define pta(x, a, b) rep(i, a, b) cout << x[i] << " \n"[i == b];
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
template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
int e[N][5],nxt[N][5],vis[N][5],cnt[N];
int dfs(int u, int k, int id) {
    if (!vis[u][k]) {
        vis[u][k] = id;
        int kk = k % 3 + 1;
        if (e[u][kk] == 0) kk = 1;
        int v = 0;
        rep(i, 1, 3) if (e[e[u][kk]][i] == u) v = i;
        nxt[u][k] = e[u][kk] << 20 | v;
        return dfs(e[u][kk], v, id);
    } else
        return vis[u][k];
}
void work() {
    cin >> n;
    rep(i, 1, n) {
        cin >> x;
        rep(j, 1, x) cin >> e[i][j];
    }
    rep(i, 1, n) {
        unordered_set<int> ss, ans;
        int id = dfs(i, 0, i);
        if (id != i) {
            pt(cnt[id]);
            continue;
        };
        int u = i << 20;
        while (1) {
            int v = nxt[u >> 20][u & 3];
            int h = (u >> 20) << 20 | (v >> 20);
            if (ss.con(h)) break;
            ss.ep(h);
            pii tmp = minmax(u >> 20, v >> 20);
            ans.ep(tmp.fi << 20 | tmp.se);
            u = v;
        }
        cnt[i] = ans.size();
        pt(cnt[i]);
    }
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