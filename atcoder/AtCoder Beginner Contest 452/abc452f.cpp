#include <bits/stdc++.h>
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
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;
//  template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
//  using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
//  template <typename T, typename Compare = std::greater<T>>
//  using hp = __gnu_pbds::priority_queue<T, Compare, pairing_heap_tag>;
//  template <typename Key, typename Mapped = null_type, typename Access =
//  trie_string_access_traits<>> using tri = trie<Key, Mapped, Access, pat_trie_tag,
//  trie_prefix_search_node_update>;
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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];

class BIT {
   public:
    vi bi;
    int n;
    BIT(int _n) : n(_n) { bi.resize(n + 2, 0); }
    int lowbit(int x) { return x & -x; }
    void update(int x, int v) {
        for (; x <= n; x += lowbit(x)) bi[x] += v;
    }
    void uprange(int l, int r, int v) {
        update(l, v);
        update(r + 1, -v);
    }
    int query(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += bi[x];
        return ans;
    }
};

int solve(int k) {
    BIT bi(n);
    int l = 1;
    int cur = 0, ans = 0;
    rep(r, 1, n) {
        cur += bi.query(n) - bi.query(a[r]);
        bi.update(a[r], 1);

        while (l <= r && cur > k) {
            cur -= bi.query(a[l] - 1);
            bi.update(a[l], -1);
            l++;
        }

        ans += (r - l + 1);
    }
    return ans;
}
void work() {
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i];
    int res = solve(k) - (k ? solve(k - 1) : 0);
    pt(res);
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