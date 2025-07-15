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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
int cnt;
unordered_map<int, int> mp, mp2, mp1;
struct Node {
    int l, r, v;
    Node(int _l, int _r, int _v) : l(_l), r(_r), v(_v) {}
    bool operator<(const Node &u) const { return l < u.l; }
};
set<Node> s[N];
auto split(int p, auto &s) {
    auto it = s.low(Node(p, 0, 0));
    if (it != s.end() && it->l == p) return it;
    it--;
    int l = it->l, r = it->r, v = it->v;
    s.erase(it);
    s.insert(Node(l, p - 1, v));
    return s.ep(Node(p, r, v)).fi;
}
void assign(int l, int r, int v, auto &s) {
    auto itr = split(r + 1, s), itl = split(l, s);
    while (itl != s.begin() && prev(itl)->v == v) itl--;
    while (itr != s.end() && itr->v == v) itr++;
    l = itl->l, r = prev(itr)->r;
    s.erase(itl, itr);
    s.insert(Node(l, r, v));
}

int ask(int l, int r, auto &s) {
    int res = 0;
    auto it = s.low(Node(l, 0, 0));
    for (; it != s.end() && it->l <= r; it++) {
        res += min(it->r, r) - it->l + 1;
    }
    return res;
}
void update(int l, int r, auto &t) {
    auto it = s[0].low(l);
    for (; it != s[0].end && it->l <= r; it++) t.assign(it->l, min(it->r, r), it->v);
}
void work() {
    cin >> n >> k >> m;
    rep(i, 1, n) cin >> a[i], b[i] = a[i];
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    rep(i, 1, len) m1p[b[i]] = i;
    rep(i, 1, n) mp2[mp1[a[i]]]++;
    int l = 1;
    rep(i, 2, n) {
        if (mp2[i] != mp2[i - 1]) {
            s[0].ep(l, i - 1, mp2[l]);
            l = i;
        }
    }
    s[0].ep(l, n, mp2[l]);
    rep(i, 1, k) {
        int op, l, r, p;
        cin >> op >> l >> r >> p;
        if (!mp.con(p)) mp[p] = ++cnt, s[mp[p]].ep(1, mod, 0);

        if (op == 1) {
            update(l, r, s[mp[p]]);
        } else {
            pt(ask(l, r, s[mp[p]]));
        }
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