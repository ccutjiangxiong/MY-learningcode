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
int f2[N], g1[N], g2[N];
vi e[N];
int cnt[N], sum;
int mp1[N], mp2[N], mp3[N], ver[N];
void add(int p) {
    if (!mp1[a[p]])
        mp1[a[p]] = mp2[a[p]] = p;
    else {
        mp1[a[p]] = min(mp1[a[p]], p);
        mp2[a[p]] = max(p, mp2[a[p]]);
        sum = max(sum, mp2[a[p]] - mp1[a[p]]);
    }
}
// int cnt;
struct {
    int l, r, id;
} q[N];
unordered_map<int, int> f1;
void work() {
    cin >> n;

    rep(i, 1, n) cin >> a[i], c[i] = a[i];
    sort(c + 1, c + 1 + n);
    int len = unique(c + 1, c + 1 + n) - (c + 1);
    rep(i, 1, len) f1[c[i]] = i;
    vi m1(len + 10);
    rep(i, 1, n) a[i] = f1[a[i]];
    cin >> m;
    rep(i, 1, m) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    int B = sqrt(n);
    sort(q + 1, q + 1 + m, [&](auto u, auto v) {
        if (u.l / B == v.l / B) return u.r < v.r;
        return u.l < v.l;
    });
    int lb = -1;
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        int now = q[i].l / B;
        if (now != lb) {
            lb = now;
            sum = 0;
            r = (now + 1) * B - 1;
            l = r + 1;
            rep(v, 1, len) mp1[v] = mp2[v] = 0;
        }
        if (q[i].l / B == q[i].r / B) {
            // unordered_map<int, int> m1;
            int ans = 0;
            rep(j, q[i].l, q[i].r) {
                if (m1[a[j]])
                    ans = max(ans, j - m1[a[j]]);
                else
                    m1[a[j]] = j;
            }
            rep(j, q[i].l, q[i].r) m1[a[j]] = 0;
            b[q[i].id] = ans;
            continue;
        }
        while (r < q[i].r) add(++r);
        int mx = sum;
        tot++;
        rem(j, l - 1, q[i].l) {
            int x = a[j];
            if (ver[x] != tot) {
                ver[x] = tot;
                mp3[x] = j;
            }
            if (!mp3[x]) mp3[x] = j;
            mx = max(mx, mp3[x] - j);
            if (mp2[x]) mx = max(mx, mp2[x] - j);
        }
        b[q[i].id] = mx;
    }
    rep(i, 1, m) pt(b[i]);
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