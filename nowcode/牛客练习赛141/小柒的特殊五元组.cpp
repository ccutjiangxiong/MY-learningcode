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
#define int ill
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
// using pii = pair<int, int>;
// using piii = tuple<int, int, int>;
// using vi = vector<int>;
// using vii = vector<pii>;
// using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;
using ll = long long;
using cpx = complex<ld>;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);

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
void nrd(T &...a) {
    ((a = rd()), ...);
}
template <typename... T>
void nwt(T... a) {
    ((wt(a), putchar(' ')), ...);
    putchar('\n');
}
int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
// vi e[N];
ost<int> tr[10];
int pre[10][N];
struct BIT {
    int n;
    vector<int> t;
    BIT(int _n = 0) : n(_n), t(n + 1, 0) {}
    void init(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) t[x] += v;
    }
    int sum(int x) const {
        int s = 0;
        for (; x > 0; x -= x & -x) s += t[x];
        return s;
    }
    int range(int l, int r) const { return l > r ? 0 : (sum(r) - sum(l - 1)); }
};

void work() {
    // cin >> n;
    n = rd();
    // rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) a[i] = rd();
    int M = n;
    BIT b2(M), b3(M), b4(M), b5(M);
    vector<int> dp2(n + 1), dp3(n + 1), dp4(n + 1), dp5(n + 1);
    rep(i, 1, n) {
        int v = a[i];
        dp2[i] = b2.range(v + 1, M);
        b2.add(v, 1);
        dp3[i] = b3.range(1, v - 1);
        b3.add(v, dp2[i]);
        dp4[i] = b4.range(1, v - 1);
        b4.add(v, dp3[i]);
        dp5[i] = b5.range(v + 1, M);
        b5.add(v, dp4[i]);
    }
    ill ans = 0;
    rep(i, 1, n) ans += dp5[i];
    wt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // if (ti == 0) cin >> ti;
    // while (ti--) {
    work();
    // }
    return 0;
}