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
using ll = int64_t;
using cpx = complex<ld>;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];

int pre[N], aans[N];
map<int, int> ss[500][500];
void insert(auto ss, int a, int b) {
    auto it = ss.upp(a);
    if (it == ss.begin())
        ss[a] = b;
    else {
        it--;
        if (it->se <= b) return;
        ss[a] = b;
    }
    it = ss.find(a);
    auto nxt = next(it);
    while (nxt != ss.end() && nxt->se >= b) ss.erase(nxt++);
}
int ask(auto ss, int a) {
    auto it = ss.upp(a);
    if (it == ss.begin())
        return -1;
    else
        return prev(it)->se;
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i], pre[i] = pre[i - 1] + a[i];
    rep(i, 1, n) rep(j, i, n) ss[i][j].clear();
    rep(i, 1, n) aans[i] = -1, ss[i][i].ep(0, 0);
    rep(len, 2, n) rep(st, 1, n - len + 1) rep(m, st, st + len - 2) {
        int l = st, r = st + len - 1;
        int l1 = pre[m] - pre[l - 1], l2 = pre[r] - pre[m];
        int imb = abs(l1 - l2);
        int x1 = ask(ss[l][m], imb), x2 = ask(ss[m + 1][r], imb);
        if (x1 == -1 || x2 == -1) continue;
        int x = min(l1, l2) * ceil(log2(l1 + l2)) + x1 + x2;
        insert(ss[l][r], imb, x);
        if (l == 1 && r == n) aans[m] = x;
    }
    pta(aans, 1, n - 1);
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