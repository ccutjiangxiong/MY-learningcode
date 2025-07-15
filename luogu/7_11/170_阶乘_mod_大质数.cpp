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

int ti = 1, n, m, k, ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];
const u64 Mod = 1000391835649, Inv = 7381400789652078591, R2 = 251003689260, Phi = Mod - 1;
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
    friend bool operator==(const Mont& a, int b) noexcept { return a.get() == b; }
    friend bool operator==(int a, const Mont& b) noexcept { return a == b.get(); }
    friend auto operator<=>(const Mont& a, int b) noexcept { return a.get() <=> b; }
    explicit operator int() const { return get(); }
    u64 get() const {
        u64 x = reduce(v);
        return (int)(x >= Mod ? x - Mod : x);
    }
    friend ostream& operator<<(ostream& os, const Mont& m) { return os << m.get(); }
};
const int MOD = 1000391835649;
using mint = Mont;
using vmi = vector<Mont>;
const int p = 1000391835649, g = 7, gi = 285826238757;
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
    mint& operator[](int i) {
        if (i >= (int)a.size()) a.resize(i + 1);
        return a[i];
    }
    mint operator[](int i) const { return (i < (int)a.size() ? a[i] : mint(0)); }
    Poly operator*(const Poly& b) const { return Poly(Mul(a, b.a)); }
};
mint f[N], inv1[N], inv2[N];
void init(int n, int p) {
    f[0] = inv1[1] = inv1[0] = 1;
    rep(i, 1, n) f[i] = f[i - 1] * i;
    inv2[n] = mint::inv(f[n]);
    rep(i, 2, n) inv1[i] = -(p / i) * inv1[p % i];
    rem(i, n, 1) inv2[i - 1] = inv2[i] * i;
}
vmi Shift(const vmi& y, int m) {
    int n = sz(y) - 1;
    inv2[n] = mint::inv(f[n]);
    vmi u(n + 1), v(2 * n + 1), invb(2 * n + 1), tmp(2 * n + 1);
    rep(i, 0, n) u[i] = y[i] * ((n - i) & 1 ? mint(-1) : 1) * inv2[i] * inv2[n - i];
    mint ba = m - n;
    tmp[0] = 1;
    rep(k, 1, 2 * n) tmp[k] = tmp[k - 1] * (ba + k);
    invb[2 * n] = mint::inv(tmp[2 * n]);
    rem(k, 2 * n, 1) invb[k - 1] = invb[k] * (ba + k);
    v[0] = mint::inv(ba);
    rep(k, 1, 2 * n) v[k] = tmp[k - 1] * invb[k];
    auto conv = Poly::Mul(v, u);
    mint P = 1;
    rep(k, m - n, m) P *= k;
    vmi res(n + 1);
    for (int x = 0; x <= n; x++) {
        res[x] = conv[n + x] * P;
        if (x < n) P = P * mint(m + x + 1) * v[x];
    }
    return res;
}


void work() {
    init(sqrt(MOD) + 10, MOD);
    // Fac(MOD);
    FacSu(MOD);
    cin >> n;
    rep(i, 1, n) {
        cin >> x;
        pt(ask2(x, sqrt(MOD)) - ask2(x - 1, sqrt(MOD)));
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