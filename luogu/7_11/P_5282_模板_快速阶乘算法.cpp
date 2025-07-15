#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctzll(a)
#define cnt1(a) __builtin_popcountll(a)
#define cnt0(a) __builtin_clzll(a)
#define odd1(a) __builtin_parityll(a)
#define all(a) a.begin(), a.end()
#define allp(a) a->begin(), a->end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
// #define int long long
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

int ti = 1, n, m, k, ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
template <const int mod>
struct modInt {
    modInt(const int x = 0) : num((x % mod + mod) % mod) {}
    explicit operator int() { return num; }
    static constexpr int phi_v = mod - 1;
    static modInt fastPow(modInt a, int b) {
        if (b < 0) return fastPow(inv(a), -b);
        b = b % (phi_v);
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
    static modInt inv(const modInt x) { return fastPow(x, mod - 2); }
    friend std::ostream& operator<<(std::ostream& ou, const modInt& x) { return ou << x.num, ou; }
    friend std::istream& operator>>(std::istream& in, modInt& x) { return in >> x.num, in; }
    constexpr modInt& operator+=(const modInt& o) noexcept {
        num = ((__int128)num + o.num) % mod;
        return *this;
    }
    constexpr modInt& operator-=(const modInt& o) noexcept { return *this += -o; }
    constexpr modInt& operator*=(const modInt& o) noexcept {
        num = ((__int128)num * o.num) % mod;
        return *this;
    }
    constexpr modInt& operator/=(const modInt& o) noexcept { return *this *= inv(o); }
    friend constexpr modInt operator^(modInt a, int e) noexcept { return fastPow(a, e); }
    constexpr modInt operator-() const noexcept { return (mod - num) % mod; }
    friend constexpr auto operator<=>(const modInt& a, const modInt& b) noexcept = default;
    constexpr modInt& operator++() noexcept { return *this += 1; }
    constexpr modInt& operator--() noexcept { return *this -= 1; }
    friend constexpr auto operator+(modInt a, const auto& b) noexcept { return a += b; }
    friend constexpr auto operator-(modInt a, const auto& b) noexcept { return a -= b; }
    friend constexpr auto operator*(modInt a, const auto& b) noexcept { return a *= b; }
    friend constexpr auto operator/(modInt a, const auto& b) noexcept { return a /= b; }
    int num;
};
const int MOD = 998244353;
using mint = modInt<MOD>;
using vmi = vector<mint>;
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

class Poly {
   public:
    vmi a;
    Poly() = default;
    Poly(vmi v) : a(std::move(v)) { normalize(); }
    void normalize() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }
    int deg() const { return (int)a.size() - 1; }

   private:
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

   public:
    static vmi shift_eval(const vmi& y, int m) {
        int n = sz(y) - 1;
        vmi f(n + 1), invf(n + 1);
        f[0] = 1;
        rep(i, 1, n) f[i] = f[i - 1] * i;
        invf[n] = mint::inv(f[n]);
        rem(i, n, 1) invf[i - 1] = invf[i] * i;
        vmi u(n + 1);
        rep(i, 0, n) {
            // if (i == 0) pt(invf[0], "--dfadsf");
            mint a = ((n - i) & 1) ? mint(-1) : mint(1);
            u[i] = y[i] * a * invf[i] * invf[n - i];
        }
        vmi v(2 * n + 1);
        rep(k, 0, 2 * n) v[k] = mint::inv(mint(m - n + k));
        auto conv = (Poly(u) * Poly(v)).a;
        mint P = 1;
        rep(k, m - n, m) P *= k;
        vmi res(n + 1);
        for (int x = 0; x <= n; x++) {
            res[x] = conv[n + x] * P;
            if (x < n) P = P * mint(m + x + 1) * v[x];
        }
        return res;
    }
    mint& operator[](int i) {
        if (i >= (int)a.size()) a.resize(i + 1);
        return a[i];
    }
    mint operator[](int i) const { return (i < (int)a.size() ? a[i] : mint(0)); }

    Poly operator*(const Poly& b) const { return Poly(Mul(a, b.a)); }
};

int stk[N], cur;
int Stk[N], curStk;
vmi b, c, d;
inline int get_fac(int n) {
    int pos = curStk, s = sqrt(n) + 1e-6;
    mint invs = mint::inv(s);
    for (int i = s; i > 1; i >>= 1) Stk[++curStk] = i;
    c.resize(2);
    c[0] = 1, c[1] = s + 1;
    for (int l = Stk[curStk]; curStk > pos; l = Stk[--curStk]) {
        d = Poly::shift_eval(c, (l >> 1) + 1);
        c.resize(2 * sz(c));
        for (int i = 0; i < sz(d); ++i) c[sz(d) + i] = d[i];
        int x = (int)(invs * mint(l >> 1));
        d = Poly::shift_eval(c, (int)(invs * mint(l >> 1)));
        for (int i = 0; i < sz(c); ++i) c[i] *= d[i];

        if (l & 1)
            rep(i, 0, l) c[i] *= mint(i * s + l);
        else
            c.resize(l + 1);
    }

    mint res = 1;
    for (int i = s * s + 1; i <= n; ++i) res *= mint(i);
    for (int i = 0; i < s; ++i) res *= c[i];

    return (int)res;
}

void work() {
    cin >> n;
    rep(i, 1, n) {
        cin >> x >> y;
        pt(get_fac(x));
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