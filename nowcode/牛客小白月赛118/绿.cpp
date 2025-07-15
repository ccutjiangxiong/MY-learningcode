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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
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

int ti, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;

template <const int mod>
class modInt {  // 有模数
   public:
    modInt(const int x = 0)
        :  // 由数字构造，可隐式进行
          num(x % mod) {}
    explicit operator int()  // 转换回数字，必须显式进行
    {
        return num;
    }
    friend std::ostream& operator<<(std::ostream& out, const modInt& item)  // 重载 C++ 标准输出
    {
        out << item.num;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, modInt& x) {
        int v;
        in >> v;
        x = modInt(v);
        return in;
    }
    static constexpr int phi() {
        int res = mod, x = mod;
        for (int p = 2; p * p <= x; ++p) {
            if (x % p == 0) {
                while (x % p == 0) x /= p;
                res = res / p * (p - 1);
            }
        }
        if (x > 1) res = res / x * (x - 1);
        return res;
    }
    static constexpr int phi_v = phi();

    static modInt fastPow(modInt a, int b)  // 快速幂，静态函数
    {
        if (b < 0) return fastPow(inv(a), -b);
        b = b % (phi_v) + phi_v;
        modInt res(1);
        for (; b; a = a * a, b >>= 1)
            if (b & 1) res = res * a;
        return res;
    }
    template <typename... Ts>
    modInt pow(Ts... exps) const {
        int e = 1;
        ((e = ((__int128)e * ((exps % phi_v + phi_v) % phi_v)) % phi_v), ...);
        return fastPow(*this, e);
    }
    static modInt inv(
        const modInt x)  // 费马小定理乘法逆元，静态函数，没有加安全措施，请使用者注意 mod 要是质数
    {
        return fastPow(x, mod - 2);
    }
    friend modInt operator+(const modInt& lhs, const modInt& rhs)  // 重载加法
    {
        return (lhs.num + rhs.num) % mod;
    }
    modInt& operator+=(const modInt& ano) {
        num = (num + ano.num) % mod;
        return *this;
    }
    friend modInt operator*(const modInt& lhs, const modInt& rhs)  // 重载乘法
    {
        return lhs.num * rhs.num % mod;
    }
    modInt& operator*=(const modInt& ano) {
        num = num * ano.num % mod;
        return *this;
    }
    friend modInt operator-(const modInt& lhs, const modInt& rhs)  // 重载减法
    {
        int tmp = lhs.num - rhs.num;
        return tmp < 0 ? tmp + mod : tmp;
    }
    modInt& operator-=(const modInt& ano) {
        *this = *this - ano;
        return *this;
    }
    friend modInt operator/(
        const modInt& lhs,
        const modInt& rhs)  // 重载除法，注意要保证 rhs 有逆元存在（下取整除法请转换回数字进行）
    {
        return (lhs * inv(rhs)).num % mod;
    }
    friend modInt operator^(modInt base, int exp) { return fastPow(base, exp); }
    modInt& operator^=(int exp) {
        *this = *this ^ exp;
        return *this;
    }
    friend bool operator==(const modInt& lhs, const modInt& rhs) { return lhs.num == rhs.num; }
    friend bool operator!=(const modInt& lhs, const modInt& rhs) { return lhs.num != rhs.num; }
    modInt operator+(int rhs) const { return *this + modInt(rhs); }
    modInt operator-(int rhs) const { return *this - modInt(rhs); }
    modInt operator*(int rhs) const { return *this * modInt(rhs); }
    modInt operator/(int rhs) const { return *this / modInt(rhs); }
    modInt& operator+=(int rhs) { return *this += modInt(rhs); }
    modInt& operator-=(int rhs) { return *this -= modInt(rhs); }
    modInt& operator*=(int rhs) { return *this *= modInt(rhs); }
    modInt& operator/=(int rhs) { return *this /= modInt(rhs); }
    modInt& operator++() { return *this += 1; }
    modInt& operator--() { return *this -= 1; }

    modInt operator-() const { return modInt(0) - *this; }
    // 友元版本（左侧为整型）
    friend modInt operator+(int lhs, const modInt& rhs) { return modInt(lhs) + rhs; }
    friend modInt operator-(int lhs, const modInt& rhs) { return modInt(lhs) - rhs; }
    friend modInt operator*(int lhs, const modInt& rhs) { return modInt(lhs) * rhs; }
    friend modInt operator/(int lhs, const modInt& rhs) { return modInt(lhs) / rhs; }

    friend bool operator<(const modInt& a, const modInt& b) { return a.num < b.num; }
    friend bool operator>(const modInt& a, const modInt& b) { return a.num > b.num; }
    friend bool operator<=(const modInt& a, const modInt& b) { return a.num <= b.num; }
    friend bool operator>=(const modInt& a, const modInt& b) { return a.num >= b.num; }
    // 与整型混合：
    friend bool operator==(const modInt& a, int b) { return a == modInt(b); }
    friend bool operator!=(const modInt& a, int b) { return a != modInt(b); }

   private:
    int num;
};
const int MOD = 1e9 + 7;
using mint = modInt<MOD>;
void work() {
    cin >> n;
    string s;
    cin >> s;
    pt((mint(2) ^ n ^ sz(s)) - 1);
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