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
int isp[N], pri[N], phi[N], mu[N], cnt = 0;
void euler(int n) {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isp[i])
      pri[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
    for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
      isp[i * pri[j]] = 1;
      phi[i * pri[j]] = phi[i] * (pri[j] - (i % pri[j] == 0));
      mu[i * pri[j]] = i % pri[j] ? -mu[i] : 0;
      if (i % pri[j] == 0)
        break;
    }
  }
}
int MOD = 998244353;
int qpow(int a, int b, int p) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = (ill)a * ans % p;
    a = (ill)a * a % p;
    b >>= 1;
  }
  return ans;
}
// p为质数
int invp(int a, int p) { return qpow(a, p - 2, p); }
int exgcd(int a, int b, int &x, int &y) {
  if (b == 0)
    return a + (x = 1) + (y = 0) - 1;
  int x1, y1;
  int gcd = exgcd(b, a % b, x1, y1);
  x = y1, y = x1 - (a / b) * y1;
  return gcd;
}
int invp2(int a, int p) {
  int x = 0, y = 0;
  return exgcd(a, p, x, y) == 1 ? (x % p + p) % p : -1;
}
ill excrt(vii &f) {
  ill x = 0, M = 1;
  int k1, k2;
  for (auto [a, b] : f) {
    ill c = ((b - x) % a + a) % a, d = exgcd(M, a, k1, k2);
    if (c % d)
      return -1;
    ill mod = a / d, k = (c / d) * k1 % mod;
    x = (x + M * k) % (M * mod);
    M *= mod;
  }
  return (x % M + M) % M;
}
void work() {
  ll n, m;
  int k;
  cin >> n >> m >> k;
  vector<pii> p(k);
  unordered_map<int, int> rc, cc;
  rc.reserve(k * 2 + 10);
  cc.reserve(k * 2 + 10);
  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    p[i] = {x, y};
    ++rc[x];
    ++cc[y];
  }
  ll a = 0;
  for (auto &e : p) {
    if (rc[e.fi] == 1 && cc[e.se] == 1)
      ++a;
  }
  ll zr = n - (ll)rc.size();
  ll zc = m - (ll)cc.size();
  ll b = zr * zc;
  ll f = n * m - k;
  ll ans = 0;
  if (a) {
    ll e = f - n - m + 2;
    ans = (ans + a % MOD * qpow(2, e, MOD)) % MOD;
  }
  if (b) {
    ll e = f - n - m + 1;
    ans = (ans + b % MOD * qpow(2, e, MOD)) % MOD;
  }
  cout << ans << endl;
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