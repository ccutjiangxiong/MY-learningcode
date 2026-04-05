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
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 0, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
int isp[N], pri[N], phi[N], mu[N], cnt = 0;
void euler(int n) {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
            phi[i * pri[j]] = phi[i] * (pri[j] - (i % pri[j] == 0));
            mu[i * pri[j]] = i % pri[j] ? -mu[i] : 0;
            if (i % pri[j] == 0) break;
        }
    }
}

int dp[N][33];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i], c[i] = a[i];
    rep(i, 1, n) cin >> b[i];
    a[0] = a[n + 1] = 1;
    c[0] = c[n + 1] = 1;
    int ans = 0;
    rep(i, 0, n) rep(j, 0, 25) dp[i][j] = -inf;
    dp[0][0] = 0;
    pri[0] = 1;
    rep(i, 1, n) {
        int x = gcd(c[i - 1], c[i]);
        int y = gcd(c[i], c[i + 1]);
        int u = x * y / gcd(x, y);
        // pt(i,u,b[i]);
        if (u > b[i]) {
            rep(k, 0, 25) if (gcd(a[i - 1] * pri[k], a[i]) == x) dp[i][0] =
                max(dp[i][0], dp[i - 1][k]);
            continue;
        }
        if (u != c[i]) {
            rep(k, 0, 25) {
                if (gcd(a[i - 1] * pri[k], u) == x) dp[i][0] = max(dp[i][0], dp[i - 1][k] + 1);
            }
            a[i] = u;
            continue;
        }
        // dp[i][0] = dp[i - 1][0];
        rep(j, 0, 25) rep(k, 0, 25) {
            if (a[i] * pri[j] <= b[i] && gcd(a[i - 1] * pri[k], a[i] * pri[j]) == x) {
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + (j != 0));
            }
        }
        int res = 0;
        rep(i, 0, 25) res = max(dp[n][i], ans);
        // pt(i,res);
    }
    rep(i, 0, 25) ans = max(dp[n][i], ans);
    pt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    euler(N - 5);
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}