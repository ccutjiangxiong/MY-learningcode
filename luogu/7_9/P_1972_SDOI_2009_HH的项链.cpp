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
    for (auto* h : {__VA_ARGS__}) rep(i, 0, (n)) h[i] = x;
#define me2(x, n, m, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, 0, (n)) rep(j, 0, (m)) h[i][j] = x;
#define fi1(x, n1, n2, ...) \
    for (auto* h : {__VA_ARGS__}) rep(i, (n1), (n2)) h[i] = x;
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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e9 + 3;
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
char buf[1 << 21], *p1 = buf, *p2 = buf;
char gc() {
    if (p1 == p2) {
        size_t bytesRead = fread(buf, 1, 1 << 21, stdin);
        p2 = buf + bytesRead;
        p1 = buf;
        if (bytesRead == 0) return EOF;
    }
    return *p1++;
}
inline int rd() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f *= -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }
    return x * f;
}
inline void wt(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) wt(x / 10);
    putchar(x % 10 + '0');
}
template <typename... T>
void nrd(T&... a) {
    ((a = rd()), ...);
}
template <typename... T>
void nwt(T... a) {
    ((wt(a), putchar(' ')), ...);
    putchar('\n');
}
int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vii e[N], g;
int len, num[N], mi[N], id[N];
struct Point {
    int x, y, id, d;
    bool operator<(const Point& u) const { return x == u.x ? y < u.y : x < u.x; }
} p[N];
void adde(int u, int v, int w) {}
void add(int x, int d, int v) {
    for (; x <= len; x += x & -x)
        if (v < mi[x]) mi[x] = v, id[x] = d;
}
int ask(int x) {
    int res = inf, d = inf;
    for (; x; x -= x & -x)
        if (mi[x] < res) res = mi[x], d = id[x];
    return d;
}
int cal(auto& p1, auto& p2) { return abs(p1.x - p2.x) + abs(p1.y - p2.y); }
void solve() {
    sort(p + 1, p + 1 + n);
    rep(i, 1, n) num[i] = p[i].d = p[i].y - p[i].x;
    sort(num + 1, num + n + 1);
    len = unique(num + 1, num + n + 1) - num - 1;
    rep(i, 1, len) mi[i] = id[i] = inf;
    rem(i, n, 1) {
        p[i].d = low(num + 1, num + len + 1, p[i].d) - num;
        p[i].d = len - p[i].d + 1;

        int x = ask(p[i].d);
        if (x != inf) {
            int u = p[i].id, v = p[x].id, w = cal(p[i], p[x]);
            e[u].pb(v, w), e[v].pb(u, w);
        }
        add(p[i].d, i, p[i].x + p[i].y);
    }
}

int prim() {
    int cost = 0;
    vi vis(n + 1, 0);
    std::priority_queue<piii, viii, greater<>> pq;
    pq.push({0, 1, 0});
    while (!pq.empty()) {
        auto [w, u, fa] = pq.top();
        pq.pop();
        if (vis[u]++) continue;
        cost += w;
        if (fa) g.pb(fa, u);
        for (auto [v, w] : e[u])
            if (!vis[v]) pq.push({w, v, u});
    }
    return cost;
}
vi E[N];
void mmst() {
    solve();
    rep(i, 1, n) swap(p[i].x, p[i].y);
    solve();
    rep(i, 1, n) p[i].x = -p[i].x;
    solve();
    rep(i, 1, n) swap(p[i].x, p[i].y);
    solve();
    prim();
    for (auto [u, v] : g) E[u].pb(v), E[v].pb(u);
}
int cnt[N], sum;
void add(int x) {
    if (!cnt[x]) sum++;
    cnt[x]++;
}
void del(int x) {
    cnt[x]--;
    if (!cnt[x]) sum--;
}
struct {
    int l, r, id;
} q[N];
int l = 1, r = 0;
void update(int i) {
    while (l > q[i].l) add(a[--l]);
    while (r < q[i].r) add(a[++r]);
    while (l < q[i].l) del(a[l++]);
    while (r > q[i].r) del(a[r--]);
    b[q[i].id] = sum;
}
void dfs(int u, int fa) {
    update(u);
    for (int v : E[u])
        if (v != fa) dfs(v, u);
}
int hilbert(int x, int y, int p = 21, int r = 0) {
    if (!p) return 0;
    int h = 1 << (p - 1), s = ((x >= h) << 1) | (y >= h);
    s = (s + r) & 3;
    int d[] = {3, 0, 0, 1};
    int sub = 1LL << (2 * p - 2), ans = s * sub;
    int add = hilbert(x & (h - 1), y & (h - 1), p - 1, (r + d[s]) & 3);
    return (s == 1 || s == 2) ? ans + add : ans + sub - add - 1;
}

void work() {
    // cin >> m;
    m = rd();
    rep(i, 1, m) a[i] = rd();
    // cin >> n;
    n = rd();
    rep(i, 1, n) {
        // cin >> p[i].x >> p[i].y;
        p[i].x = rd();
        p[i].y = rd();
        p[i].id = i;
        q[i].l = p[i].x;
        q[i].r = p[i].y;
        q[i].id = i;
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    vector<long long> ord(n + 1);
    rep(i, 1, n) ord[i] = hilbert(q[i].l, q[i].r);
    sort(order.begin(), order.end(), [&](int u, int v) { return ord[u] < ord[v]; });

    // 3) 初始化 Mo
    l = 1;
    r = 0;
    sum = 0;
    me1(0, m + 2, cnt);

    // 4) 按排好序的顺序滑动区间并记录答案
    for (int idx : order) {
        update(idx);
        b[idx] = sum;
    }

    // 5) 输出
    rep(i, 1, n) wt(b[i]), putchar('\n');
}

// …existing code…
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}