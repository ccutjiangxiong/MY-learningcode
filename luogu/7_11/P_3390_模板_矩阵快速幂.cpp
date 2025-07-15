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
// …existing code…

// 通用矩阵模板，支持加、乘、幂、行列式
template <typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;
    Matrix(int _n, int _m) : n(_n), m(_m), a(n, vector<T>(m)) {}
    // 单位矩阵
    static Matrix identity(int sz) {
        Matrix I(sz, sz);
        for (int i = 0; i < sz; i++) I.a[i][i] = 1;
        return I;
    }
    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }
    // 矩阵乘法
    Matrix operator*(const Matrix& o) const {
        Matrix r(n, o.m);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                for (int j = 0; j < o.m; j++) r.a[i][j] += a[i][k] * o.a[k][j];
        return r;
    }
    Matrix& operator*=(const Matrix& o) { return *this = *this * o; }
    // 快速幂
    Matrix pow(long long k) const {
        Matrix res = identity(n), t = *this;
        while (k) {
            if (k & 1) res *= t;
            t *= t;
            k >>= 1;
        }
        return res;
    }
    auto inv_det() const -> tuple<bool, Matrix, T> {
        assert(n == m);
        Matrix A = *this;
        Matrix B = identity(n);
        T det = 1;
        for (int i = 0; i < n; i++) {
            int pivot = i;
            for (int j = i; j < n; j++)
                if (A.a[j][i] != T(0)) {
                    pivot = j;
                    break;
                }
            if (A.a[pivot][i] == T(0)) return {false, Matrix(0, 0), T(0)};
            if (pivot != i) {
                swap(A.a[pivot], A.a[i]);
                swap(B.a[pivot], B.a[i]);
                det = -det;
            }
            // 记录主元
            T pv = A.a[i][i];
            det *= pv;
            T invv = T(1) / pv;
            // 归一化主行
            for (int j = 0; j < n; j++) {
                A.a[i][j] *= invv;
                B.a[i][j] *= invv;
            }
            // 消去其他行
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                T factor = A.a[j][i];
                for (int k = 0; k < n; k++) {
                    A.a[j][k] -= factor * A.a[i][k];
                    B.a[j][k] -= factor * B.a[i][k];
                }
            }
        }
        return {true, B, det};
        // …existing code…
    };
};
// …existing code…
void work() {
    int n;
    cin >> n;
    // read into a matrix of Mont (mod 998244353)
    Matrix<mint> A(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll x;
            cin >> x;
            A[i][j] = mint(x);
        }
    }
    // 1) Reduce A to upper Hessenberg form by similarity (row+column) transforms
    for (int k = 0; k < n - 1; k++) {
        int pivot = -1;
        for (int i = k + 1; i < n; i++) {
            if (A[i][k] != mint(0)) {
                pivot = i;
                break;
            }
        }
        if (pivot == -1) continue;
        // swap row k+1<->pivot and col k+1<->pivot
        if (pivot != k + 1) {
            swap(A.a[pivot], A.a[k + 1]);
            for (int i = 0; i < n; i++) {
                swap(A[i][pivot], A[i][k + 1]);
            }
        }
        mint invv = mint(1) / A[k + 1][k];
        for (int i = k + 2; i < n; i++) {
            mint factor = A[i][k] * invv;
            if (factor == mint(0)) continue;
            // eliminate A[i][k]
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k + 1][j];
            }
            // apply matching column op
            for (int j = 0; j < n; j++) {
                A[j][k + 1] += factor * A[j][i];
            }
        }
    }
    // extract diagonal α[i]=A[i][i] and super-diag β[j]=A[j-1][j]
    vector<mint> alpha(n), sd(n + 1);
    for (int i = 0; i < n; i++) {
        alpha[i] = A[i][i];
        if (i >= 1) sd[i + 1] = A[i - 1][i];
    }
    // 2) recurrence for f[m](x)=det(xI_m – H_m)
    //    f[0]=1, deg(f[m])=m,  f[m] = (x-α[m-1]) f[m-1]
    //      – ∑_{t=1..m-1} f[m-t-1]·(∏_{j=m-t+1..m}β_j)·h_{m-t,m}
    vector<vector<mint>> f(n + 1, vector<mint>(n + 1));
    f[0][0] = mint(1);
    for (int m = 1; m <= n; m++) {
        // (x - α[m-1]) * f[m-1]
        for (int j = 0; j < m; j++) {
            mint v = f[m - 1][j];
            if (v == mint(0)) continue;
            f[m][j] -= alpha[m - 1] * v;
            f[m][j + 1] += v;
        }
        // correction terms
        for (int t = 1; t < m; t++) {
            int pos = m - t;                // 1-based in the formula
            mint hval = A[pos - 1][m - 1];  // H_{pos,m}
            if (hval == mint(0)) continue;
            // prod of β_j for j=pos+1..m  (β_j = sd[j])
            mint prod = mint(1);
            for (int j = pos + 1; j <= m; j++) prod *= sd[j];
            mint mul = hval * prod;
            // subtract mul * f[m-t-1]
            for (int j = 0; j <= m - t - 1; j++) {
                f[m][j] -= f[m - t - 1][j] * mul;
            }
        }
    }
    // output coefficients f[n][0..n]
    for (int i = 0; i <= n; i++) {
        cout << f[n][i].get() << (i < n ? ' ' : '\n');
    }
}
// …existing code…
// …existing code…

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}