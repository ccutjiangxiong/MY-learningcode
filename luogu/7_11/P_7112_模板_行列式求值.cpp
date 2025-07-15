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
// int Mod, phi_v;
int Mod, phi_v;

struct Barrett {
    unsigned long long p, inv;
    Barrett(unsigned long long mod = 1) : p(mod) {
        inv = (~0ULL) / p + 1;  // floor(2^64 / p)
    }
    unsigned int reduce(unsigned long long x) const {
        unsigned long long q = (__uint128_t(x) * inv) >> 64;
        unsigned long long r = x - q * p;
        return r < p ? r : r - p;
    }
} bar;

struct modInt {
    int num;

    modInt(const int x = 0) : num(bar.reduce((x % Mod + Mod) % Mod)) {}

    explicit operator int() const noexcept { return num; }

    static modInt fastPow(modInt a, int b) {
        if (b < 0) return fastPow(inv(a), -b);
        modInt res(1);
        for (; b; a = a * a, b >>= 1)
            if (b & 1) res = res * a;
        return res;
    }

    template <typename... Ts>
    modInt pow(Ts... exps) const {
        int e = 1;
        ((e = (1LL * e * exps % phi_v)), ...);
        return fastPow(*this, e);
    }

    static modInt inv(const modInt x) { return fastPow(x, Mod - 2); }

    constexpr modInt& operator+=(const modInt& o) noexcept {
        num += o.num;
        if (num >= Mod) num -= Mod;
        return *this;
    }

    constexpr modInt& operator-=(const modInt& o) noexcept {
        num -= o.num;
        if (num < 0) num += Mod;
        return *this;
    }

    constexpr modInt& operator*=(const modInt& o) noexcept {
        num = bar.reduce(1ULL * num * o.num);
        return *this;
    }

    constexpr modInt& operator/=(const modInt& o) noexcept { return *this *= inv(o); }

    friend constexpr modInt operator+(modInt a, const modInt& b) noexcept { return a += b; }
    friend constexpr modInt operator-(modInt a, const modInt& b) noexcept { return a -= b; }
    friend constexpr modInt operator*(modInt a, const modInt& b) noexcept { return a *= b; }
    friend constexpr modInt operator/(modInt a, const modInt& b) noexcept { return a /= b; }
    friend constexpr modInt operator^(modInt a, int e) noexcept { return fastPow(a, e); }
    constexpr modInt operator-() const noexcept { return (num ? Mod - num : 0); }
    friend constexpr auto operator<=>(const modInt& a, const modInt& b) noexcept = default;
    constexpr modInt& operator++() noexcept { return *this += 1; }
    constexpr modInt& operator--() noexcept { return *this -= 1; }

    friend std::ostream& operator<<(std::ostream& os, const modInt& x) { return os << x.num; }

    friend std::istream& operator>>(std::istream& is, modInt& x) {
        int v;
        is >> v;
        x = modInt(v);
        return is;
    }
};

using mint = modInt;
using vmi = vector<mint>;
template <typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;
    Matrix(int _n, int _m) : n(_n), m(_m), a(n, vector<T>(m)) {}
    static Matrix identity(int sz) {
        Matrix I(sz, sz);
        rep(i, 0, sz - 1) I.a[i][i] = 1;
        return I;
    }
    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }
    Matrix operator*(const Matrix& o) const {
        Matrix r(n, o.m);
        rep(i, 0, n - 1) rep(k, 0, m - 1) rep(j, 0, o.m - 1) r.a[i][j] += a[i][k] * o.a[k][j];
        return r;
    }
    Matrix& operator*=(const Matrix& o) { return *this = *this * o; }
    Matrix pow(long long k) const {
        Matrix res = identity(n), t = *this;
        while (k) {
            if (k & 1) res *= t;
            t *= t, k >>= 1;
        }
        return res;
    }
    int det() {
        mint res = 1;
        int w = 1;
        rep(i, 0, n - 1) rep(j, i + 1, n - 1) {
            while (a[i][i] != 0) {
                int div = (int)a[j][i] / (int)a[i][i];
                rep(k, i, n - 1) a[j][k] = (int)a[j][k] - div * (int)a[i][k];
                swap(a[i], a[j]);
                w = -w;
            }
            swap(a[i], a[j]), w = -w;
        }
        rep(i, 0, n - 1) res = a[i][i] * res;
        return (int)(res * w);
    }
    // 逆矩阵和行列式
    auto inv_det() const -> tuple<bool, Matrix, T> {
        assert(n == m);
        Matrix A = *this, B = identity(n);
        T det = 1;
        rep(i, 0, n - 1) {
            int cur = i;
            rep(j, i, n - 1) if (A[j][i] != T(0)) {
                cur = j;
                break;
            }
            if (A[cur][i] == T(0)) return {false, Matrix(0, 0), T(0)};
            if (cur != i) swap(A[cur], A[i]), swap(B.a[cur], B[i]), det = -det;
            T pv = A[i][i], inv = T(1) / pv;
            det *= pv;
            rep(j, 0, n - 1) A[i][j] *= inv, B[i][j] *= inv;
            rep(j, 0, n - 1) if (j != i) {
                T w = A[j][i];
                rep(k, 0, n - 1) A[j][k] -= w * A[i][k], B[j][k] -= w * B[i][k];
            }
        }
        return {true, B, det};
    };
    // ✅ Hessenberg 相似化
    void hessenberg() {
        for (int i = 0; i < n - 1; i++) {
            int p = -1;
            for (int j = i + 1; j < n; j++)
                if (a[j][i] != T(0)) {
                    p = j;
                    break;
                }
            if (p == -1) continue;
            swap(a[p], a[i + 1]);
            for (int j = 0; j < n; j++) swap(a[j][p], a[j][i + 1]);
            T invv = T(1) / a[i + 1][i];
            for (int j = i + 2; j < n; j++) {
                if (a[j][i] == T(0)) continue;
                T tmp = a[j][i] * invv;
                rep(k, i, n - 1) a[j][k] -= tmp * a[i + 1][k];
                rep(k, 0, n - 1) a[k][i + 1] += tmp * a[k][j];
            }
        }
    }
    // ✅ 特征多项式递推（Hessenberg专用）
    vector<T> charpoly() const {
        vector<vector<T>> p(n + 1, vector<T>(n + 1));
        p[0][0] = 1;
        rep(i, 1, n) {
            rep(m, 1, i - 1) {
                T tmp = a[m - 1][i - 1];
                rep(j, m, i - 1) tmp *= a[j][j - 1];
                rep(j, 0, n) p[i][j] -= tmp * p[m - 1][j];
            }
            rep(j, 1, n) p[i][j] += p[i - 1][j - 1];
            rep(j, 0, n) p[i][j] -= a[i - 1][i - 1] * p[i - 1][j];
        }
        return p[n];
    }
};

void work() {
    cin >> n >> m;
    Mod = m;
    // Mod = m;             // 设置模数
    bar = Barrett(Mod);  // 初始化 Barrett
    Matrix<mint> A(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> A[i][j];
    // auto [a, b, c] = A.inv_det();
    cout << A.det();
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