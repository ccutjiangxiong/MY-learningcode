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
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
int f[N][33];
void st(const int a[], int n) {
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}

int ask(int a, int b) {
    int j = log2(b - a + 1);
    int ans = max(f[a][j], f[b - (1 << j) + 1][j]);
    return ans;
}
vector<int> ss[N];
void work() {
    int s;
    cin >> n >> s >> x;
    rep(i, 1, n) cin >> a[i], b[i] = a[i] + b[i - 1];
    st(a, n);
    int cnt = 0;
    map<int, int> mp;
    res = 0;
    mp[0] = ++cnt;
    ss[1].pb(0);
    rep(i, 1, n) {
        if (!mp.con(b[i])) mp[b[i]] = ++cnt;
        if (mp.con(b[i] - s)) {
            int u = mp[b[i] - s];
            int l = 0, r = sz(ss[u]) - 1;
            int ans1 = -1, ans2 = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (ask(ss[u][mid] + 1, i) >= x)
                    l = mid + 1, ans1 = mid;
                else
                    r = mid - 1;
            }

            l = 0, r = sz(ss[u]) - 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (ask(ss[u][mid] + 1, i) <= x)
                    r = mid - 1, ans2 = mid;
                else
                    l = mid + 1;
            }
            if (ans1 != -1 && ask(ss[u][ans1] + 1, i) == x) {
                if (ans2 != -1) {
                    res += (ans1 + 1 - ans2);

                } else
                    res++;
            }
        }
        ss[mp[b[i]]].pb(i);
    }
    rep(i, 0, cnt) ss[i].clear();
    pt(res);
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