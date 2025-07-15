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
#define me(a, x) memset(a, x, sizeof(a))
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename Compare = std::greater<T>>
using hp = __gnu_pbds::priority_queue<T, Compare, pairing_heap_tag>;
template <typename Key, typename Mapped = null_type, typename Access = trie_string_access_traits<>>
using trie = trie<Key, Mapped, Access, pat_trie_tag, trie_prefix_search_node_update>;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
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
    rope<int> str,rstr;
inline void rev(int st, int ed) {
    if (st >= ed + 1) return;
    ed++;
    rope<int> tmp = str.substr(st + str.begin(), ed + str.begin());
    str = str.substr(0 + str.begin(), st + str.begin()) +
          rstr.substr(n - ed + rstr.begin(), n - st + rstr.begin()) +
          str.substr(ed + str.begin(), str.length() + str.begin());
    rstr = rstr.substr(rstr.begin(), n - ed + rstr.begin()) + tmp +
           rstr.substr(n - st + rstr.begin(), rstr.length() + rstr.begin());
}
void work() {
    cin >> n >> m;
    //     rp.push();

    rep(i, 1, n) str.append(i),rstr.append(n-i+1);
    rep(i, 1, m) {
        cin >> x >> y;
        rev(x-1,y-1);
    }
    rep(i,0,n-1) cout<<str[i]<<' ';

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