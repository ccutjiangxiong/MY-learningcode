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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
vi e[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }

void work() {
    set<int> s1, s2;
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i], s1.ep(a[i]);
    rep(i, 1, n) cin >> b[i], s2.ep(b[i]);

    int mi1 = *s1.begin(), ma1 = *s1.rbegin();
    int mi2 = *s1.begin(), ma2 = *s2.rbegin();
    if (ma1 - mi1 == 2 && s1.con(mi1 + 1)) {
        vi g;
        rep(i, 1, n) if (a[i] != mi1 + 1) g.pb(a[i]);
        rg::sort(g);
        int cnt = 0;
        rep(i, 1, n) if (a[i] != mi1 + 1) a[i] = g[cnt++];
    } else
        sort(a + 1, a + 1 + n);
    if (ma2 - mi2 == 2 && s1.con(mi2 + 1)) {
        vi g;
        rep(i, 1, n) if (b[i] != mi2 + 1) g.pb(b[i]);
        rg::sort(g);
        int cnt = 0;
        rep(i, 1, n) if (b[i] != mi2 + 1) b[i] = g[cnt++];
    } else
        sort(b + 1, b + 1 + n);
    // rep(i, 1, n) cout << a[i] << " \n"[i == n];
    // rep(i, 1, n) cout << b[i] << " \n"[i == n];

    // 判断 a 和 b 是否循环等价（Duval 最小轮换）
    auto duval = [&](const vector<int> &s) {
        int N = s.size(), i = 0, j = 1, k = 0;
        while (i < N && j < N && k < N) {
            int x = s[(i + k) % N], y = s[(j + k) % N];
            if (x == y) {
                k++;
                continue;
            }
            if (x > y)
                i += k + 1;
            else
                j += k + 1;
            if (i == j) j++;
            k = 0;
        }
        int st = min(i, j);
        vector<int> t(N);
        rep(p, 0, N - 1) t[p] = s[(st + p) % N];
        return t;
    };

    vector<int> va(n), vb(n);
    rep(i, 0, n - 1) {
        va[i] = a[i + 1];
        vb[i] = b[i + 1];
    }
    if (duval(va) == duval(vb))
        cout << "YES\n";
    else
        cout << "NO\n";
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