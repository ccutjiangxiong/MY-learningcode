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
const int p = 998244353, g = 3, gi = 332748118;  // G的逆元，使用费马小定理计算得出
// const int p = 1e9 + 7, g = 5, gi = 400000003;
static int NTT_n = 0, NTT_logn = 0;
static vi R;
static vector<vector<mint>> wn[2];
void NTT(vector<mint>& a, int op) {
    int n = a.size();
    if (n != NTT_n) {
        NTT_n = n, NTT_logn = lbt(n), R.assign(n, 0);
        rep(i, 0, n - 1) R[i] = R[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
        for (int t = 0; t < 2; t++) {
            wn[t].assign(NTT_logn + 1, {});
            for (int k = 1; k <= NTT_logn; k++) {
                int len = 1 << k, half = len >> 1;
                mint b = mint(t == 0 ? g : gi).pow((p - 1) / len);
                auto& w = wn[t][k];
                w.resize(half), w[0] = 1;
                rep(i, 1, half - 1) w[i] = w[i - 1] * b;
            }
        }
    }
    rep(i, 0, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
    for (int k = 1, len = 2; k <= NTT_logn; k++, len <<= 1) {
        int half = len >> 1;
        auto& w = wn[op == 1 ? 0 : 1][k];
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < half; j++) {
                mint u = a[i + j];
                mint v = a[i + j + half] * w[j];
                a[i + j] = u + v;
                a[i + j + half] = u - v;
            }
    }
    if (op == -1) {
        mint inv_n = mint::inv(n);
        for (auto& x : a) x *= inv_n;
    }
}
mint mod_sqrt(mint n) {
    const int p = MOD;
    if (n == 0) return 0;
    // Euler 判别
    if (n.pow((p - 1) / 2) != 1) return -1;
    // p ≡ 1 mod 2^? 做 Tonelli–Shanks：
    int S = 0;
    int q = p - 1;
    while (!(q & 1)) {
        q >>= 1;
        ++S;
    }
    // 找 z 为二次非剩余
    mint z = 2;
    while (z.pow((p - 1) / 2) != p - 1) ++z;
    mint c = z.pow(q);
    mint x = n.pow((q + 1) / 2);
    mint t = n.pow(q);
    int M = S;
    while (t != 1) {
        int i = 1;
        mint tt = (t * t);
        while (tt != 1) {
            tt = tt * tt;
            ++i;
        }
        mint b = c.pow(1LL << (M - i - 1));
        x = x * b;
        c = b * b;
        t = t * c;
        M = i;
    }
    mint r1 = x;
    mint r2 = mint(0) - x;
    return r1 < r2 ? r1 : r2;
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
        if (n <= 1) return {mint(0)};
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
        for (int i = 0; i < n; i++) diff[i] = (i < (int)A.size() ? A[i] : mint(0)) - lnB[i];
        diff[0] += 1;
        auto C = multiply_ntt(B, diff);
        C.resize(n);
        return C;
    }

    static vector<mint> poly_sqrt(vector<mint> A, int n) {
        // 基础：n=1 时直接开 a[0]
        if (n == 1) {
            mint r = mod_sqrt(A[0]);
            return {r};
        }
        int m = (n + 1) >> 1;
        // 递归求前 m 项
        auto B = poly_sqrt(A, m);
        // A/B mod x^n
        auto InvB = poly_inv(B, n);
        auto C = multiply_ntt(A, InvB);
        C.resize(n);
        // B 中高次补 0
        B.resize(n);
        // (B + C)/2
        mint inv2 = mint::inv(mint(2));
        vector<mint> S(n);
        for (int i = 0; i < n; i++) {
            S[i] = (B[i] + C[i]) * inv2;
        }
        return S;
    }

   public:
    Poly pow_k(const string& K, int n) const {
        // 1) 去掉前导 0
        string kstr = K;
        while (kstr.size() > 1 && kstr[0] == '0') kstr.erase(0, 1);
        // 2) k=0 -> 常数 1
        if (kstr == "0") {
            vector<mint> R(n);
            R[0] = 1;
            return Poly(R);
        }
        // 3) 找最低非零项 lead
        int m = a.size(), lead = 0;
        while (lead < m && a[lead] == mint(0)) ++lead;
        // 全零 -> 全零
        if (lead >= m) return Poly(vector<mint>(n, mint(0)));
        // 4) 移位递归
        if (lead > 0) {
            int need = (n + lead - 1) / lead;
            string sNeed = std::to_string((long long)need);
            bool ge =
                (kstr.size() > sNeed.size()) || (kstr.size() == sNeed.size() && kstr >= sNeed);
            if (ge) return Poly(vector<mint>(n, mint(0)));
            long long kll = 0;
            for (char c : kstr) kll = kll * 10 + (c - '0');
            int shift = lead * kll;
            vector<mint> C;
            for (int i = lead; i < m && (int)C.size() < n - shift; i++) C.push_back(a[i]);
            Poly PC(C);
            Poly PD = PC.pow_k(kstr, n - shift);
            vector<mint> R(n, mint(0));
            auto vD = PD.coeffs();
            for (int i = 0; i < (int)vD.size(); i++) R[i + shift] = vD[i];
            return Poly(R);
        }
        // 5) lead==0 且 k>0：设 A(x)=a0·B(x), B[0]=1
        long long km = 0, kph = 0, phi = MOD - 1;
        for (char c : kstr) {
            int d = c - '0';
            km = (km * 10 + d) % MOD;
            kph = (kph * 10 + d) % phi;
        }
        mint kmod = km;
        // 提取 B(x)=A(x)/a0
        // 提取 B(x)=A(x)/a0，使得 B[0]=1 且其它项也要除以 a0
        vector<mint> Bv = a;
        Bv.resize(n);
        mint a0 = Bv[0];
        mint inv_a0 = mint::inv(a0);
        for (auto& x : Bv) x *= inv_a0;  // 所有系数除以 a0
        // exp(k·ln B)
        auto L = poly_ln(Bv, n);
        for (auto& x : L) x *= kmod;
        auto S = poly_exp(L, n);
        // 乘回 a0^k
        mint a0k = a0.pow(kph);
        for (auto& x : S) x *= a0k;
        return Poly(S);
    }
    Poly operator*(const Poly& b) const { return Poly(multiply_ntt(a, b.a)); }
    Poly operator/(const Poly& b) const { return Poly(poly_div(a, b.a)); }
    Poly operator%(const Poly& b) const { return Poly(poly_mod(a, b.a)); }
    Poly sqrt(int n) const { return Poly(poly_sqrt(a, n)); }
    Poly inv(int n) const { return Poly(Poly::poly_inv(a, n)); }
    Poly exp(int n) const { return Poly(poly_exp(a, n)); }
    Poly ln(int n) const { return Poly(poly_ln(a, n)); }
    mint eval(mint x) const {
        mint res = 0;
        for (int i = deg(); i >= 0; --i) res = res * x + a[i];
        return res;
    }
};
// 新增：多项式组合 F(G(x)) mod x^{n+1}
Poly compose(const Poly& F, const Poly& G, int n) {
    int t = sqrt(n) + 1;
    int chunks = (n + t - 1) / t;
    // 1) 预处理 G^0, G^1, …, G^{t-1}
    vector<Poly> gp(t);
    gp[0] = Poly(vector<mint>{1});
    for (int i = 1; i < t; i++) {
        gp[i] = gp[i - 1] * G;
        auto v = gp[i].coeffs();
        if ((int)v.size() > n + 1) v.resize(n + 1);
        gp[i] = Poly(v);
    }
    // 2) 预处理大步 G^{t}, G^{2t}, …
    vector<Poly> big(chunks);
    big[0] = Poly(vector<mint>{1});
    Poly Gt = gp[t - 1] * G;
    {
        auto v = Gt.coeffs();
        if ((int)v.size() > n + 1) v.resize(n + 1);
        Gt = Poly(v);
    }
    for (int j = 1; j < chunks; j++) {
        big[j] = big[j - 1] * Gt;
        auto v = big[j].coeffs();
        if ((int)v.size() > n + 1) v.resize(n + 1);
        big[j] = Poly(v);
    }
    // 3) 分块累加
    Poly H(vector<mint>(n + 1));
    auto& fcoef = F.coeffs();
    for (int j = 0; j < chunks; j++) {
        Poly Sj(vector<mint>(n + 1));
        for (int i = 0; i < t; i++) {
            int idx = j * t + i;
            if (idx > F.deg()) break;
            mint c = fcoef[idx];
            if (c == 0) continue;
            auto& gpi = gp[i].coeffs();
            for (int k = 0; k < (int)gpi.size() && k <= n; k++) {
                Sj[k] += gpi[k] * c;
            }
        }
        auto tmp = Sj * big[j];
        auto& vtmp = tmp.coeffs();
        for (int k = 0; k < (int)vtmp.size() && k <= n; k++) {
            H[k] += vtmp[k];
        }
    }
    return H;
}

void work() {
    int n, m;
    cin >> n >> m;
    vector<mint> f(n + 1), g(m + 1);
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        f[i] = x;
    }
    for (int i = 0; i <= m; i++) {
        int x;
        cin >> x;
        g[i] = x;
    }
    Poly F(f), G(g);
    Poly H = compose(F, G, n);
    auto hc = H.coeffs();
    hc.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        cout << hc[i] << (i == n ? '\n' : ' ');
    }
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