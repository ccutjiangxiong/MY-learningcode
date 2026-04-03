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
//  template <typename Key, typename Mapped = null_type, typename Compare =
//  std::less<Key>> using ost = tree<Key, Mapped, Compare, rb_tree_tag,
//  tree_order_statistics_node_update>; template <typename T, typename Compare =
//  std::greater<T>> using hp = __gnu_pbds::priority_queue<T, Compare,
//  pairing_heap_tag>; template <typename Key, typename Mapped = null_type,
//  typename Access = trie_string_access_traits<>> using tri = trie<Key, Mapped,
//  Access, pat_trie_tag, trie_prefix_search_node_update>;
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
template <typename... T> void pt(T... a) {
  ((cout << a << ' '), ...);
  cout << "\n";
}

int ti = 0, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];

int dp[N][10];
void work() {
  cin >> n;

  rep(i, 1, n) cin >> a[i];
  rep(i, 1, n) cin >> b[i];
  rep(i, 1, n) cin >> c[i];
  rep(i, 0, n) rep(j, 0, 4) dp[i][j] = inf;
  a[0] = inf;
  dp[0][0] = 0;
  rep(i, 1, n) rep(j, 0, 4) {
    rep(k, 0, 4) if (a[i] + j != a[i - 1] + k) {
      int ca = 0, cb = 0;
      if (j == 0)
        ca = 2 * c[i];
      if (j == 1)
        ca = c[i];
      if (j == 3)
        ca = b[i];
      if (j == 4)
        ca = 2 * b[i];
      if (a[i] + j - 2 >= 1)
        dp[i][j] = min(dp[i][j], dp[i - 1][k] + ca);
    }
  }
  pt(min({dp[n][0], dp[n][1], dp[n][2], dp[n][3], dp[n][4]}));
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  if (ti == 0)
    cin >> ti;
  while (ti--) {
    work();
  }
  return 0;
}