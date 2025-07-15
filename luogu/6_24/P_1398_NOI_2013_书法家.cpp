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
// const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
// void be(auto edges[N]) {
//     int u, v;
//     cin >> u >> v;
//     edges[u].pb(v), edges[v].pb(u);
// }

// template <typename... T>
// void pt(T... a) {
//     ((cout << a << ' '), ...);
//     cout << "\n";
// }

// int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
// int f1[N], f2[N], g1[N], g2[N];
// vi e[N];
const int N = 154;
const int M = 504;
ll n, m, dp4, dp8, ans, INF;
ll a[M][N], s[N];
ll dp1[N][N], dp2[N][N], dp3[N][N];
ll dp5[N][N], dp6[N][N], dp7[N][N];
ll dp9[N][N], dp10[N][N], dp11[N][N];
ll s1[N][N], s2[N][N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[j][n - i + 1];
        }
    }
    memset(dp1, -63, sizeof(dp1));
    memset(dp2, -63, sizeof(dp2));
    memset(dp3, -63, sizeof(dp3));
    memset(dp5, -63, sizeof(dp5));
    memset(dp6, -63, sizeof(dp6));
    memset(dp7, -63, sizeof(dp7));
    memset(dp9, -63, sizeof(dp9));
    memset(dp10, -63, sizeof(dp10));
    memset(dp11, -63, sizeof(dp11));
    memset(s1, -63, sizeof(s1));
    memset(s2, -63, sizeof(s2));
    INF = -dp1[0][0];
    dp4 = dp8 = ans = -INF;
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + a[j][i];
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                ans = max(ans, dp11[l][r] = max(dp11[l][r], dp10[l][r]) + a[j][l] + a[j][r]);
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                dp10[l][r] = max(dp10[l][r], dp9[l][r]) + s[r] - s[l - 1];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                dp9[l][r] = max(dp9[l][r], dp8) + a[j][l] + a[j][r];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                dp8 = max(dp8, dp7[l][r]);
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                dp7[l][r] = dp6[l][r] + s[r] - s[l - 1];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                dp6[l][r] = max(dp6[l][r], dp5[l][r]) + a[j][l] + a[j][r];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 2; r <= n; r++) {
                dp5[l][r] = dp4 + s[r] - s[l - 1];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 1; r <= n; r++) {
                dp4 = max(dp4, dp3[l][r]);
            }
        }
        for (int l = 1; l <= n; l++) {
            ll tmp = -INF;
            for (int r = l + 1; r <= n; r++) {
                tmp = max(tmp, dp2[l][r - 1]);
                dp3[l][r] = max(dp3[l][r], tmp) + s[r] - s[l - 1];
            }
        }
        for (int r = 1; r <= n; r++) {
            ll tmp = s2[r + 1][r];
            for (int l = r; l; l--) {
                tmp = max(tmp, s2[l][r]);
                dp2[l][r] = max(s1[l - 1][r], tmp) + s[r] - s[l - 1];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                dp1[l][r] = max(0ll, dp1[l][r]) + s[r] - s[l - 1];
            }
        }
        for (int l = 1; l <= n; l++) {
            for (int r = n; r; r--) {
                s2[l][r] = max(dp2[l][r], s2[l][r + 1]);
            }
        }
        for (int r = 1; r <= n; r++) {
            for (int l = 1; l <= n; l++) {
                s1[l][r] = max(dp1[l][r], s1[l - 1][r]);
            }
        }
    }
    cout << ans;
}