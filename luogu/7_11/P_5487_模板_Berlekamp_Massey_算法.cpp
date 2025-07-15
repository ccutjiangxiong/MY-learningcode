#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define ranll(l, r) std::uniform_int_distribution<long long>(l, r)(rng)
#define lbt(a) __builtin_ctzll(a)
#define cnt1(a) __builtin_popcountll(a)
#define cnt0(a) __builtin_clzll(a)
#define odd1(a) __builtin_parityll(a)
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
using ll = long long;
using cpx = complex<ld>;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = unsigned __int128;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
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
const u64 Mod = 998244353, Inv = 17450252288407896063, R2 = 299560064, Phi = Mod - 1;
struct Mont {
    u64 v;
    // static void init(u64 m) {
    //     Mod = m, Inv = 1;
    //     rep(i, 1, 6) Inv *= 2 - Inv * Mod;
    //     u128 t = (u128(1) << 64) % Mod;
    //     Inv = -Inv, R2 = (u64)(t * t % Mod);
    // }
    static u64 reduce(u128 t) {
        u64 m = (u64)t * Inv;
        u64 u = (u64)((t + (u128)m * Mod) >> 64);
        return u >= Mod ? u - Mod : u;
    }
    Mont() : v(0) {}
    Mont(ll x) {
        ll y = x % (ll)Mod;
        if (y < 0) y += Mod;
        v = reduce((u128)(u64)y * R2);
    }
    static Mont pow(Mont a, ll b) {
        if (b < 0) return pow(inv(a), -b);
        Mont res(1);
        while (b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }
    static Mont inv(const Mont& a) { return pow(a, (ll)Mod - 2); }
    Mont& operator+=(const Mont& o) { return v += o.v, v = v >= Mod ? v - Mod : v, *this; }
    Mont& operator-=(const Mont& o) { return v = v < o.v ? v + Mod : v, v -= o.v, *this; }
    Mont& operator*=(const Mont& o) { return v = reduce((u128)v * o.v), *this; }
    Mont& operator/=(const Mont& o) { return *this *= inv(o); }
    friend Mont operator-(const Mont& a) noexcept { return Mont(0) - a; }
    friend Mont operator+(Mont a, const Mont& b) noexcept { return a += b; }
    friend Mont operator-(Mont a, const Mont& b) noexcept { return a -= b; }
    friend Mont operator*(Mont a, const Mont& b) noexcept { return a *= b; }
    friend Mont operator/(Mont a, const Mont& b) noexcept { return a /= b; }
    auto operator<=>(const Mont& o) const noexcept = default;
    bool operator==(const Mont& o) const noexcept = default;
    explicit operator int() const { return get(); }
    u64 get() const {
        u64 x = reduce(v);
        return (int)(x >= Mod ? x - Mod : x);
    }
    friend ostream& operator<<(ostream& os, const Mont& m) { return os << m.get(); };
    friend istream& operator>>(istream& in, Mont& m) {
        int v;
        return in >> v, m = v, in;
    }
};
using mint = Mont;
using vmi = vector<Mont>;
const int p = 998244353, g = 3, gi = 332748118;
static int NTT_n = 0, NTT_logn = 0;
static vi R;
static vector<vmi> wn[2];
void NTT(vmi& a, int op) {
    int n = a.size();
    if (n != NTT_n) {
        NTT_n = n, NTT_logn = lbt(n), R.assign(n, 0);
        rep(i, 0, n - 1) R[i] = R[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
        for (int t = 0; t < 2; t++) {
            wn[t].assign(NTT_logn + 1, {});
            for (int k = 1; k <= NTT_logn; k++) {
                int len = 1 << k, half = len >> 1;
                mint b = Mont::pow(mint(t == 0 ? g : gi), (p - 1) / len);
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
class Poly {
   public:
    vmi a;
    Poly() = default;
    Poly(vmi v) : a(std::move(v)) { normalize(); }
    void normalize() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }
    int deg() const { return (int)a.size() - 1; }
    static vmi Mul(vmi A, vmi B) {
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
    static vmi Inv(vmi A, int n) {
        if (n == 1) return {mint::inv(A[0])};
        int m = (n + 1) >> 1, len = 1;
        A.resize(n);
        auto B = Inv(A, m);
        while (len < 2 * n) len <<= 1;
        A.resize(len), B.resize(len);
        NTT(A, 1), NTT(B, 1);
        for (int i = 0; i < len; ++i) B[i] = (mint(2) - A[i] * B[i]) * B[i];
        NTT(B, -1), B.resize(n);
        return B;
    }
    static vmi Div(vmi A, vmi B) {
        int n = A.size(), m = B.size();
        if (n < m) return {};
        rg::reverse(A), rg::reverse(B);
        B = Inv(B, n - m + 1);
        auto Qr = Mul(A, B);
        Qr.resize(n - m + 1);
        rg::reverse(Qr);
        return Qr;
    }
    static vmi Mod(vmi A, vmi B) {
        int n = A.size(), m = B.size();
        if (n < m) return (A.resize(m - 1), A);
        auto Q = Div(A, B);
        auto C = Mul(Q, B);
        auto R = (Poly(A) - Poly(C)).a;
        R.resize(m - 1);
        return R;
    }
    static vmi De(const vmi& A) {
        int n = A.size();
        if (n <= 1) return {mint(0)};
        vmi D(n - 1);
        for (int i = 1; i < n; i++) D[i - 1] = A[i] * i;
        return D;
    }
    static vmi Inte(const vmi& A) {
        int n = A.size();
        vmi I(n + 1);
        I[0] = 0;
        for (int i = 0; i < n; i++) I[i + 1] = A[i] / (i + 1);
        return I;
    }
    // 多项式 ln(A) mod x^n，要求 A[0]=1
    static vmi Ln(vmi A, int n) {
        A.resize(n);
        auto D = De(A);
        auto inv = Inv(A, n);
        auto tmp = Mul(D, inv);
        tmp.resize(n - 1);
        auto L = Inte(tmp);
        L.resize(n);
        return L;
    }
    // 多项式 exp(A) mod x^n，要求 A[0]=0
    static vmi Exp(vmi A, int n) {
        if (n == 1) return {mint(1)};
        int m = (n + 1) >> 1;
        auto B = Exp(A, m);
        auto lnB = Ln(B, n);
        vmi diff(n);
        for (int i = 0; i < n; i++) diff[i] = (i < (int)A.size() ? A[i] : mint(0)) - lnB[i];
        diff[0] += 1;
        auto C = Mul(B, diff);
        C.resize(n);
        return C;
    }
    mint& operator[](int i) {
        if (i >= (int)a.size()) a.resize(i + 1);
        return a[i];
    }
    mint operator[](int i) const { return (i < (int)a.size() ? a[i] : mint(0)); }
    Poly operator+(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vmi c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] + b[i];
        return Poly(c);
    }
    Poly operator-(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vmi c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] - b[i];
        return Poly(c);
    }
    Poly operator*(const Poly& b) const { return Poly(Mul(a, b.a)); }
    Poly operator/(const Poly& b) const { return Poly(Div(a, b.a)); }
    Poly operator%(const Poly& b) const { return Poly(Mod(a, b.a)); }
    Poly inv(int n) const { return Poly(Poly::Inv(a, n)); }
    Poly exp(int n) const { return Poly(Exp(a, n)); }
    Poly ln(int n) const { return Poly(Ln(a, n)); }
    Poly de() const { return De(a); }
    Poly inte() const { return Inte(a); }
    mint eval(mint x) const {
        mint res = 0;
        rem(i, deg(), 0) res = res * x + a[i];
        return res;
    }
    Poly Pow_k(const string& K, int n) const {
        mint kmod = 0;
        for (char c : K) kmod = kmod * 10 + (c - '0');
        auto L = Ln(a, n);
        for (auto& x : L) x *= kmod;
        return Poly(Exp(L, n));
    }
    Poly Sqrt(int n) const {
        vmi A = a;
        A.resize(n);
        mint inv2 = mint::inv(mint(2));
        vmi B(1, mint(1));
        for (int len = 1; len < n; len <<= 1) {
            int lim = len << 1;
            vmi F = A, H = B;
            F.resize(lim), H.resize(lim);
            vmi I = Inv(H, lim), T = Mul(F, I), NB(lim);
            T.resize(lim);
            for (int i = 0; i < lim; ++i) NB[i] = (H[i] + T[i]) * inv2;
            B.swap(NB);
        }
        B.resize(n);
        return Poly(B);
    }
    static Poly Pow_mod(Poly A, int k, Poly P) {
        Poly res({1});
        for (; k; k >>= 1) {
            if (k & 1) res = res * A % P;
            A = A * A % P;
        }
        return res;
    };
};
// 常系数齐次线性递推
mint solve(long long n, int k, const vector<int>& f, const vector<int>& a) {
    if (n < k) return mint(a[n]);
    Poly P(vmi(k + 1));
    P[k] = 1;
    for (int i = 0; i < k; ++i) P[i] = -f[k - 1 - i];
    Poly res({1}), x({0, 1});
    res = Poly::Pow_mod(x, n, P);
    mint ans = 0;
    for (int i = 0; i < k; ++i) ans += res[i] * a[i];
    return ans;
}
// 短线性递推式
vmi BM(const vmi& s) {
    vmi C = {1}, B = {1};
    int L = 0, m = 1;
    mint b = 1;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        mint d = s[i];
        for (int j = 1; j <= L; j++) d += C[j] * s[i - j];
        if (d == 0) {
            m++;
            continue;
        }
        if (2 * L <= i) {
            vmi T = C;
            mint coef = d / b;
            if (C.size() < m + B.size()) C.resize(m + B.size(), 0);
            for (int j = 0; j < B.size(); j++) C[j + m] -= coef * B[j];
            L = i + 1 - L, B = T, b = d, m = 1;
        } else {
            mint coef = d / b;
            if (C.size() < m + B.size()) C.resize(m + B.size(), 0);
            for (int j = 0; j < B.size(); j++) C[j + m] -= coef * B[j];
            m++;
        }
    }
    return C;
}
mint nth_term(const vmi& P, const vmi& C, ll k) {
    int L = C.size() - 1;
    if (k < P.size()) return P[k];
    vmi F(L + 1);
    for (int i = 0; i <= L; i++) F[i] = C[L - i];
    Poly mod_poly(F), base({0, 1}), res({1});
    res = Poly::Pow_mod(base, k, F);
    mint ans = 0;
    for (int i = 0; i < L; i++)
        if (i < res.a.size()) ans += res.a[i] * P[i];
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll k;
    cin >> n >> k;
    vmi P(n);
    for (auto& x : P) {
        ll t;
        cin >> t;
        x = mint(t);
    }

    vmi C = BM(P);
    if (C.size() > 1) {
        for (int i = 1; i < C.size(); i++) cout << -C[i] << " \n"[i == C.size() - 1];
    } else
        cout << '\n';
    cout << nth_term(P, C, k) << '\n';
    return 0;
}
