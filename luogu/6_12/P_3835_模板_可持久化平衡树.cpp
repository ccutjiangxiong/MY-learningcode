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
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define low lower_bound
#define upp upper_bound
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;
template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
// using size_type
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
vi e[N];
rope<int> *ve[N];
int rak(int x, int i) { return low(allp(ve[i]), x) - ve[i]->begin(); }
void in(int x, int i) { ve[i]->insert(rak(x, i), x); }
void era(int x, int i) {
    int p = rak(x, i);
    if (p < ve[i]->size() && (*ve[i])[p] == x) ve[i]->erase(p, 1);
}
int mi = -(1ll << 31) + 1, ma = (1ll << 31) - 1;

void work() {
    cin >> n;
    ve[0] = new rope<int>();
    rep(i, 1, n) {
        cin >> x >> y >> z;
        ve[i] = new rope<int>(*ve[x]);
        if (y == 1) in(z, i);
        if (y == 2) era(z, i);
        if (y == 3) pt(rak(z, i) + 1);
        if (y == 4) pt((*ve[i])[z - 1]);
        if (y == 5) {
            int p = rak(z, i);
            pt(p == 0 ? mi : (*ve[i])[p - 1]);
        }
        if (y == 6) {
            int p = rak(z + 1, i);
            pt(p < ve[i]->size() ? (*ve[i])[p] : ma);
        }
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