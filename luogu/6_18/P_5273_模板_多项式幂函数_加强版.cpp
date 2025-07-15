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
const int N = 3e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
using vmi = vector<mint>;
const int p = 998244353, g = 3, gi = 332748118;
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
    // 基于就地减法的减法
    Poly operator-(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vector<mint> c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] - b[i];
        return Poly(c);
    }

    // 供外部取系数
    const vector<mint>& coeffs() const { return a; }

   private:
    static vector<mint> multiply_ntt(vector<mint> A, vector<mint> B) {
        int n = A.size(), m = B.size();
        if (n == 0 || m == 0) return {};
        int sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        A.resize(sz), B.resize(sz);
        NTT(A, 1), NTT(B, 1);
        rep(i, 0, sz - 1) A[i] *= B[i];
        NTT(A, -1), A.resize(n + m - 1);
        return A;
    }
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
    static vector<mint> poly_div(vector<mint> A, vector<mint> B) {
        int n = A.size(), m = B.size();
        if (n < m) return {};
        rg::reverse(A), rg::reverse(B);
        B = poly_inv(B, n - m + 1);
        auto Qr = multiply_ntt(A, B);
        Qr.resize(n - m + 1);
        rg::reverse(Qr);
        return Qr;
    }
    static vector<mint> poly_mod(vector<mint> A, vector<mint> B) {
        int n = A.size(), m = B.size();
        if (n < m) return (A.resize(m - 1), A);
        auto Q = poly_div(A, B);
        auto C = multiply_ntt(Q, B);
        auto R = (Poly(A) - Poly(C)).coeffs();
        R.resize(m - 1);
        return R;
    }
    static vector<mint> poly_derivative(const vector<mint>& A) {
        int n = A.size();
        if (n <= 1) return {0};
        vector<mint> D(n - 1);
        for (int i = 1; i < n; i++) D[i - 1] = A[i] * i;
        return D;
    }
    // 不定积分
    static vector<mint> poly_integral(const vector<mint>& A) {
        int n = A.size();
        vector<mint> I(n + 1);
        I[0] = 0;
        for (int i = 0; i < n; i++) I[i + 1] = A[i] / (i + 1);
        return I;
    }
    // 多项式 ln(A) mod x^n，要求 A[0]=1
    static vector<mint> poly_ln(vector<mint> A, int n) {
        A.resize(n);
        auto D = poly_derivative(A);
        auto Inv = poly_inv(A, n);
        auto tmp = multiply_ntt(D, Inv);
        tmp.resize(n - 1);
        auto L = poly_integral(tmp);
        L.resize(n);
        return L;
    }
    // 多项式 exp(A) mod x^n，要求 A[0]=0
    static vector<mint> poly_exp(vector<mint> A, int n) {
        if (n == 1) return {mint(1)};
        int m = (n + 1) >> 1;
        auto B = poly_exp(A, m);
        auto lnB = poly_ln(B, n);
        vector<mint> diff(n);
        for (int i = 0; i < n; i++) diff[i] = (i < (int)A.size() ? A[i] : 0) - lnB[i];
        diff[0] += 1;
        auto C = multiply_ntt(B, diff);
        C.resize(n);
        return C;
    }

   public:
    Poly pow(const string& K, int n) const {
        vmi R(n), Bv = a, C;
        if (K == "0") return R[0] = 1, R;
        int m = a.size(), l = 0;
        while (l < m && a[l] == 0) ++l;
        if (l >= m) return vmi(n, 0);
        if (l > 0) {
            int ne = (n + l - 1) / l;
            string s = std::to_string(ne);
            bool ge = (sz(K) > sz(s) || (sz(K) == sz(s)) && K >= s);
            if (ge) return vmi(n, 0);
            int kll = 0;
            for (char c : K) kll = kll * 10 + (c - '0');
            int sh = l * kll;
            for (int i = l; i < m && sz(C) < n - sh; i++) C.push_back(a[i]);
            Poly PC(C), PD = PC.pow(K, n - sh);
            vmi R(n, 0), vD = PD.a;
            for (int i = 0; i < sz(vD); i++) R[i + sh] = vD[i];
            return Poly(R);
        }
        int km = 0, kph = 0, phi = MOD - 1;
        for (char c : K) km = (km * 10 + (c - '0')) % MOD, kph = (kph * 10 + (c - '0')) % phi;
        Bv.resize(n);
        mint a0 = Bv[0], inv_a0 = mint::inv(a0);
        for (auto& x : Bv) x *= inv_a0;
        auto L = poly_ln(Bv, n);
        for (auto& x : L) x *= km;
        auto S = poly_exp(L, n);
        mint a0k = a0.pow(kph);
        for (auto& x : S) x *= a0k;
        return S;
    }
    Poly operator*(const Poly& b) const { return Poly(multiply_ntt(a, b.a)); }
    Poly operator/(const Poly& b) const { return Poly(poly_div(a, b.a)); }
    Poly operator%(const Poly& b) const { return Poly(poly_mod(a, b.a)); }
    Poly inv(int n) const { return Poly(Poly::poly_inv(a, n)); }
    Poly exp(int n) const { return Poly(poly_exp(a, n)); }
    Poly ln(int n) const { return Poly(poly_ln(a, n)); }
    mint eval(mint x) const {
        mint res = 0;
        for (int i = deg(); i >= 0; --i) res = res * x + a[i];
        return res;
    }
};

void work() {
    int n;
    string K;
    cin >> n >> K;
    vmi A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    Poly f(A);
    auto ans = f.pow(K, n);
    pta(ans.coeffs(), 0, n - 1);
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