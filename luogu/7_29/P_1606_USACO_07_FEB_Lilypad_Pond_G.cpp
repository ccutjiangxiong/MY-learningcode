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
int gr[55][55];
vi e[N];
int dir[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, -2}, {1, 2}, {-1, 2}, {-1, -2}};
int vis[N];
void add(int x, int y, int id1) {
    int id = m * (x - 1) + y;
    if (gr[x][y] == 2 || vis[id] == id1) return;
    vis[id] = id1;
    rep(i, 0, 7) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
            int id2 = m * (nx - 1) + ny;
            if (gr[nx][ny] == 1)
                add(nx, ny, id1);
            else
                e[id1].pb(id2);
        }
    }
}

void dij(int s) {
    hp<pii> pq;
    me(a, 0x3f);
    pq.push({a[s] = 0, s});
    b[s] = 1;
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (c[u]++) continue;
        for (int v : e[u]) {
            if (a[u] + 1 == a[v]) b[v] += b[u];

            if (a[u] + 1 < a[v]) b[v] = b[u], pq.push({a[v] = a[u] + 1, v});
        }
    }
}

void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> gr[i][j];
    int s = 0, t = 0;
    rep(i, 1, n) rep(j, 1, m) {
        int id = m * (i - 1) + j;
        if (gr[i][j] == 4) t = id;
        if (gr[i][j] == 3) s = id;
        if (gr[i][j] != 4) add(i, j, id);
    }
    // pt(s, t);
    dij(s);
    if (a[t] >= 0x3f3f3f3f3f3f3f3fLL) {
        cout << -1 << '\n';
    } else {
        cout << a[t] - 1 << '\n' << b[t] << '\n';
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