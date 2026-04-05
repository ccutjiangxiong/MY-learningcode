#include <bits/stdc++.h>
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
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;
//  template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
//  using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
//  template <typename T, typename Compare = std::greater<T>>
//  using hp = __gnu_pbds::priority_queue<T, Compare, pairing_heap_tag>;
//  template <typename Key, typename Mapped = null_type, typename Access =
//  trie_string_access_traits<>> using tri = trie<Key, Mapped, Access, pat_trie_tag,
//  trie_prefix_search_node_update>;
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
vi e[N];
// 0 0 0 0 0
// 1 0 1 0 1
// 1 2 0 1 2
// 1 2 3 0 1
// 1 2 3 4
const int p = 998244353;
int pre[N];
void work() {
    cin >> n >> m;

    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> b[i];
    rep(i, 1, n) pre[i] = (pre[i - 1] + a[i]) % p;
    int s1 = 0;
    rep(i, 1, n)(s1 += (a[i] * i)) %= p;
    int s2 = 0;
    rep(i, 1, m)(s2 += (b[i])) %= p;
    int p1 = s1 * s2 % p;
    int p2 = 0;
    rep(j, 1, m) {
        if (b[j] == 0) continue;
        for (int k = 1; k * j <= n; k++) {
            int l = k * j;
            int r = min(n, (k + 1) * j - 1);
            int sua = (pre[r] - pre[l - 1] + p) % p;
            int cb = sua * k % p;
            cb = cb * j % p;
            cb = cb * b[j] % p;
            p2 = (p2 + cb) % p;
        }
    }
    int ans = (p1 - p2) % p;
    pt((ans + p) % p);
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