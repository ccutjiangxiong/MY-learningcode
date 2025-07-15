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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
int ne[N], z[N], p[N], d[N];
void kmp(string &s) {
    int n = s.size();
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && (s[i - 1] != s[j])) j = ne[j];
        if (s[i - 1] == s[j]) j++;
        ne[i] = j;
    }
}
void zfunc(string &s) {
    int n = s.size();
    z[1] = n;
    int l, r = 0;
    for (int i = 2; i <= n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
        while (z[i] + i <= n && s[z[i]] == s[i - 1 + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
int manacher(string &t) {
    int ans = 0;
    int m = t.size();
    string s = "*#";
    for (char ch : t) s += ch, s += '#';
    s += '!';
    int n = s.size() - 1;
    d[1] = 1;
    for (int i = 2, l = 1; i <= n; i++) {
        d[i] = min(d[2 * l - i], l + d[l] - i);
        while (s[i - d[i]] == s[i + d[i]]) d[i]++;
        if (i + d[i] > l + d[l]) l = i;
        ans = max(ans, d[i] - 1);
    }
    return ans;
}
void work() {
    string s, t;
    cin >> s;
    t = "matiji";
    kmp(t);
    int j = 0;
    rep(i, 1, sz(s)) {
        while (j && s[i - 1] != t[j]) j = ne[j];
        if (s[i - 1] == t[j]) j++;
        if (j == sz(t)) ans++, j = ne[j];
    }
    pt(ans);
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