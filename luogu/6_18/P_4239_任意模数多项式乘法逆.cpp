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
int isp[N], pri[N], Phi[N], cnt = 0;
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}
int invp(int a, int p) { return qpow(a, p - 2, p); }
cpx A[N];
void FTT(vector<cpx>& A, int op) {
    int n = A.size();
    vi R(n + 1);
    for (int i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    for (int i = 0; i < n; i++)
        if (i < R[i]) swap(A[i], A[R[i]]);
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
    if (op == -1) {
        for (int i = 0; i < n; i++) A[i] /= n;
    }
}

vi MTT(const vi& A, const vi& B, int mod) {
    int na = A.size(), nb = B.size();
    if (na == 0 || nb == 0) return {};
    int need = na + nb - 1, N = 1;
    while (N < need) N <<= 1;
    const int S = 1 << 15, M = S - 1;
    vector<cpx> fa(N), fb(N);
    for (int i = 0; i < na; i++) fa[i] = cpx(A[i] & M, A[i] >> 15);
    for (int i = 0; i < nb; i++) fb[i] = cpx(B[i] & M, B[i] >> 15);
    FTT(fa, 1), FTT(fb, 1);
    vector<cpx> f0(N), f1(N), f2(N);
    for (int i = 0; i < N; i++) {
        int j = (N - i) & (N - 1);
        cpx a1 = (fa[i] + conj(fa[j])) * cpx(0.5, 0);
        cpx a2 = (fa[i] - conj(fa[j])) * cpx(0, -0.5);
        cpx b1 = (fb[i] + conj(fb[j])) * cpx(0.5, 0);
        cpx b2 = (fb[i] - conj(fb[j])) * cpx(0, -0.5);
        f0[i] = a1 * b1;
        f1[i] = a1 * b2 + a2 * b1;
        f2[i] = a2 * b2;
    }
    FTT(f0, -1), FTT(f1, -1), FTT(f2, -1);
    vi C(need);
    for (int i = 0; i < need; i++) {
        int v0 = llround(f0[i].real());
        int v1 = llround(f1[i].real());
        int v2 = llround(f2[i].real());
        int x = (v0 + ((v1 % mod) << 15) + ((v2 % mod) << 30)) % mod;
        if (x < 0) x += mod;
        C[i] = x;
    }
    return C;
}

vi INV(const vi& A, int n) {
    vi B(1, invp(A[0], mod));
    for (int m = 1; m < n; m <<= 1) {
        int c = min(2 * m, n);
        vi AA(c), E(c);
        for (int i = 0; i < c; i++) AA[i] = A[i];
        vi AB = MTT(B, AA, mod);
        AB.resize(c);
        E[0] = (2 - AB[0] + mod) % mod;
        for (int i = 1; i < c; i++) E[i] = (mod - AB[i]) % mod;
        B = MTT(B, E, mod);
        B.resize(c);
    }
    return B;
}

void work() {
    int n;
    cin >> n;
    vi A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    auto G = INV(A, n);
    for (int i = 0; i < n; i++) cout << G[i] << (i + 1 == n ? '\n' : ' ');
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