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
#define ld  double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define low lower_bound
#define upp upper_bound
#define ftl llround
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
using ll = long long;
using cpx = complex<ld>;
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
cpx A[N];
void FFT(vector<cpx>& A, int op) {
    int n = A.size();
    vi R(n + 1);
    rep(i, 0, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    rep(i, 0, n - 1) if (i < R[i]) swap(A[i], A[R[i]]);
    for (int m = 2; m <= n; m <<= 1) {
        cpx dw(cosl(2 * PI / m), sinl(2 * PI / m) * op);
        for (int i = 0; i < n; i += m) {
            cpx wk(1, 0);
            for (int j = i; j < i + m / 2; j++) {
                cpx x = A[j], y = A[j + m / 2] * wk;
                A[j] = x + y, A[j + m / 2] = x - y;
                wk *= dw;
            }
        }
    }
    if (op == -1) rep(i, 0, n - 1) A[i] /= n;
}

vi MTT(const vi& A, const vi& B, int mod) {
    int n = A.size(), m = B.size();
    if (!n || !m) return {};
    int len = n + m - 1, N = 1;
    while (N < len) N <<= 1;
    const int S = 1 << 15, MASK = S - 1;
    vector<cpx> P(N), Q(N);
    rep(i, 0, n - 1) P[i] = cpx(A[i] & MASK, A[i] >> 15);
    rep(i, 0, m - 1) Q[i] = cpx(B[i] & MASK, B[i] >> 15);
    FFT(P, 1), FFT(Q, 1);
    vector<cpx> U(N), V(N);
    rep(i, 0, N - 1) {
        int j = i ? N - i : 0;
        cpx a0 = (P[i] + conj(P[j])) * cpx(0.5, 0);
        cpx a1 = (P[i] - conj(P[j])) * cpx(0, -0.5);
        cpx b0 = (Q[i] + conj(Q[j])) * cpx(0.5, 0);
        cpx b1 = (Q[i] - conj(Q[j])) * cpx(0, -0.5);
        U[i] = a0 * b0 + cpx(0, 1) * a1 * b0;
        V[i] = a0 * b1 + cpx(0, 1) * a1 * b1;
    }
    FFT(U, -1), FFT(V, -1);
    vi C(len);
    for (int i = 0; i < len; i++) {
        auto [ur, ui, vr, vi] =
            make_tuple(ftl(U[i].real()), ftl(U[i].imag()), ftl(V[i].real()), ftl(V[i].imag()));
        C[i] = ((ur + (ui + vr) % mod * (1 << 15) + vi % mod * (1 << 30) % mod) % mod + mod) % mod;
    }
    return C;
}

void work() {
    int deg_a, deg_b, mod;
    cin >> deg_a >> deg_b >> mod;
    vector<int> A(deg_a + 1), B(deg_b + 1);
    for (int i = 0; i <= deg_a; i++) cin >> A[i];
    for (int i = 0; i <= deg_b; i++) cin >> B[i];

    auto C = MTT(A, B, mod);
    for (int i = 0; i < (int)C.size(); i++) cout << C[i] << (i + 1 == (int)C.size() ? '\n' : ' ');
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