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
    friend Mont operator+(Mont a, const Mont& b) noexcept { return a += b; }
    friend Mont operator-(Mont a, const Mont& b) noexcept { return a -= b; }
    friend Mont operator*(Mont a, const Mont& b) noexcept { return a *= b; }
    friend Mont operator/(Mont a, const Mont& b) noexcept { return a /= b; }
    friend Mont operator-(const Mont& a) noexcept { return Mont(0) - a; }
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
            if (cur != i) swap(A[cur], A[i]), swap(B.a[cur], B[i]), det = 0;
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
    int n;
    cin >> n;
    Matrix<mint> A(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> A[i][j];
    A.hessenberg();
    auto poly = A.charpoly();
    for (auto x : poly) cout << x << ' ';
    int a = 1, b = 2;
    // assert(a == b);
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