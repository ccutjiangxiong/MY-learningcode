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
const int N = 3e6 + 5, mod = 998244353, inf = 1e18 + 3;
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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
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
        return (long long)lhs.num * rhs.num % mod;
    }
    modInt& operator*=(const modInt& ano) {
        num = (long long)num * ano.num % mod;
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
        return fastPow(rhs, mod - 2) * lhs;
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
    int num;
};

const int MOD = 998244353;
using mint = modInt<MOD>;
const int p = 998244353, g = 3, gi = 332748118;  // G的逆元，使用费马小定理计算得出
// const int p = 1e9 + 7, g = 5, gi = 400000003;
void NTT(vector<mint>& A, int op) {
    int n = A.size();
    vi R(n + 1);
    rep(i, 0, n - 1) R[i] = R[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
    rep(i, 0, n - 1) if (i < R[i]) swap(A[i], A[R[i]]);
    for (int i = 2; i <= n; i <<= 1) {
        mint g1 = mint(op == 1 ? g : gi).pow((p - 1) / i);
        for (int j = 0; j < n; j += i) {
            mint gk = 1;
            rep(k, j, j - 1 + i / 2) {
                mint x = A[k], y = gk * A[k + i / 2];
                A[k] = (x + y), A[k + i / 2] = (x - y + p);
                gk *= g1;
            }
        }
    }
    if (op == -1) {
        mint inv_n = mint::inv(n);
        rep(i, 0, n - 1) A[i] *= inv_n;
    }
}
class Poly {
    vector<mint> a;

   public:
    Poly() {}
    Poly(const vector<mint>& v) : a(v) { normalize(); }

    void normalize() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }

    int deg() const { return (int)a.size() - 1; }

    mint& operator[](int i) {
        if (i >= (int)a.size()) a.resize(i + 1);
        return a[i];
    }
    mint operator[](int i) const { return (i < (int)a.size() ? a[i] : mint(0)); }

    Poly operator+(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vector<mint> c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] + b[i];
        return Poly(c);
    }

    Poly operator-(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vector<mint> c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] - b[i];
        return Poly(c);
    }

   private:
    static vector<mint> multiply_ntt(vector<mint> A, vector<mint> B) {
        int n = A.size(), m = B.size();
        if (n == 0 || m == 0) return {};
        int sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        A.resize(sz), B.resize(sz);
        NTT(A, 1), NTT(B, 1);
        rep(i, 0, sz - 1) A[i] *= B[i];
        NTT(A, -1);
        A.resize(n + m - 1);
        return A;
    }
    // 改为 static 成员函数
    static vector<mint> poly_inv(vector<mint> A, int n) {
        if (n == 1) return {mint::inv(A[0])};
        int m = (n + 1) >> 1, len = 1;
        A.resize(n);
        auto B = poly_inv(A, m);
        while (len < 2 * n) len <<= 1;
        A.resize(len), B.resize(len);
        NTT(A, 1), NTT(B, 1);
        for (int i = 0; i < len; ++i) B[i] = (mint(2) - A[i] * B[i]) * B[i];
        NTT(B, -1), B.resize(n);
        return B;
    }

   public:
    Poly operator*(const Poly& b) const { return Poly(multiply_ntt(a, b.a)); }
    // 直接调用类内的 static poly_inv
    Poly inv(int n) const { return Poly(Poly::poly_inv(a, n)); }

    mint eval(mint x) const {
        mint res = 0;
        for (int i = deg(); i >= 0; --i) res = res * x + a[i];
        return res;
    }
};

// …(前面不变)…

void work() {
    int n;
    cin >> n;
    vector<mint> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    // 1) 预处理阶乘和逆阶乘
    vector<mint> fac(n), invfac(n);
    fac[0] = 1;
    for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i;
    invfac[n - 1] = mint::inv(fac[n - 1]);
    for (int i = n - 1; i > 0; i--) invfac[i - 1] = invfac[i] * i;

    // 2) 构造 F[i] = A[i]/i!，G[i] = (-1)^i / i!
    vector<mint> F(n), G(n);
    for (int i = 0; i < n; i++) {
        F[i] = A[i] * invfac[i];
        G[i] = (i & 1 ? -mint(1) : mint(1)) * invfac[i];
    }

    // 3) 卷积 F * G
    int sz = 1;
    while (sz < n + n) sz <<= 1;
    F.resize(sz);
    G.resize(sz);
    NTT(F, 1);
    NTT(G, 1);
    for (int i = 0; i < sz; i++) F[i] *= G[i];
    NTT(F, -1);
    F.resize(n);

    // 4) 恢复 b[i] = F[i] * i!
    for (int i = 0; i < n; i++) {
        cout << (F[i] * fac[i]) << (i + 1 == n ? '\n' : ' ');
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}
