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
const int p = 998244353;
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
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}
// p为质数
int invp(int a, int p) { return qpow(a, p - 2, p); }
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) return a + (x = 1) + (y = 0) - 1;
    int x1, y1;
    int gcd = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return gcd;
}
int invp2(int a, int p) {
    int x = 0, y = 0;
    return exgcd(a, p, x, y) == 1 ? (x % p + p) % p : -1;
}
ill excrt(vii& f) {
    ill x = 0, M = 1;
    int k1, k2;
    for (auto [a, b] : f) {
        ill c = ((b - x) % a + a) % a, d = exgcd(M, a, k1, k2);
        if (c % d) return -1;
        ill mod = a / d, k = (c / d) * k1 % mod;
        x = (x + M * k) % (M * mod);
        M *= mod;
    }
    return (x % M + M) % M;
}
int f[N], g[N], de[N], s[2222][2222];
// 预处理阶乘和逆元，支持组合数快速计算
void initc(int n, int p) {
    f[0] = 1;
    rep(i, 1, n) f[i] = f[i - 1] * i % p;
    g[n] = qpow(f[n], p - 2, p);
    rem(i, n, 1) g[i - 1] = g[i] * i % p;
}
int getc(int n, int m, int p) { return f[n] * g[m] % p * g[n - m] % p; }
// s[n][m] 表示将 n 个元素分成 m 个非空循环排列的方案数（第一类斯特林数），结果对 p 取模。
void inits1(int n, int m, int p) {
    s[0][0] = 1;
    rep(i, 1, n) rep(j, 1, m) s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * (i - 1)) % p;
}
// s[n][m] 表示将 n 个元素分成 m 个非空集合的方案数（第二类斯特林数），结果对 p 取模。
void inits2(int n, int m, int p) {
    s[0][0] = 1;
    rep(i, 1, n) rep(j, 1, m) s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % p;
}
// de[n] 表示 n 个元素的错排方案数（即每个元素都不在原来的位置），结果对 p 取模。
void initd(int n, int p) {
    de[1] = 0, de[2] = 1;
    rep(i, 3, n) de[i] = (i - 1) * (de[i - 1] + de[i - 2]) % p;
}
// Lucas定理，计算组合数 C(n, m) 模 p，支持大 n
int lucas(int n, int m, int p) {
    return m == 0 ? 1 : lucas(n / p, m / p, p) * getc(n % p, m % p, p) % p;
}
// 计算Catalan数（卡特兰数），模 p
int catalan(int n, int m, int p) { return (getc(n + m, n, p) - getc(n + m, n - 1, p) + p) % p; }
// 计算隔板法组合数，模 mod n：总物品数  m：分组数（隔板数+1）  k：每组至少有 k 个物品
int sab(int n, int m, int k, int mod) { return lucas(n - (k - 1) * m - 1, m - 1, mod); }
void work() {
    cin >> n;
    string s;
    cin >> s;
    int c1 = 0, c2 = 0;
    for (char ch : s) {
        if (ch == 'j') c1++;
        if (ch == 'o') c2++;
    }

    int odd = (n + 1) / 2;  // 1~n中奇数的数量
    int even = n / 2;       // 1~n中偶数的数量
    int q = n - c1 - c2;    // '?'的数量

    // 需要从q个'?'中选出x个作为奇数位置
    int x = odd - c1;
    if (x < 0 || x > q) {
        cout << 0 << endl;
        return;
    }

    // 计算组合数 C(q, x)
    int comb = getc(q, x, p);

    // 总方案数 = C(q, x) * odd! * even!
    int ans = (long long)comb * f[odd] % p * f[even] % p;
    cout << ans << endl;
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