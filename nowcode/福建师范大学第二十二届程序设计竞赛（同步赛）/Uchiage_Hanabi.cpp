#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a);
#define cnt1(a) __builtin_popcount(a);
#define cnt0(a) __builtin_clz(a);
#define odd1(a) __builtin_parity(a);
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;

#define lc p << 1
#define rc (p << 1 | 1)
struct Node {
    int l, r, sum;
} tr[N * 4];
int w[N];
inline int &sum(int a) { return tr[a].sum; }
inline int &l(int a) { return tr[a].l; }
inline int &r(int a) { return tr[a].r; }
void pushup(int p) { sum(p) = max(sum(rc), sum(lc)); }
void build(int p, int l, int r) {
    tr[p] = {l, r, w[l]};
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    pushup(p);
}

void update(int p, int x, int k) {
    if (x <= l(p) && x >= r(p)) {
        sum(p) = k;
        return;
    }
    int m = (l(p) + r(p)) >> 1;
    if (x <= m) update(lc, x, k);
    if (x > m) update(rc, x, k);
    pushup(p);
}

int query(int p, int x, int y) {
    if (x <= l(p) && y >= r(p)) return sum(p);
    int m = (l(p) + r(p)) >> 1;
    int sum = -inf;
    if (x <= m) sum = max(query(lc, x, y), sum);
    if (y > m) sum = max(query(rc, x, y), sum);
    return sum;
}
void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, dp[N][502], n, m, d, a[N], b[N], t[N], p[N];
int h[N], g[N];
void work() {
    cin >> n >> m >> d;
    rep(i, 1, m) cin >> a[i] >> b[i] >> t[i];
    // build(1, 1, n);
    rep(j, 2, n - 1) p[j] = -inf;
    p[1] = p[n] = 0;
    // rep(j, 1, n) update(1, j, -inf);
    // update(1, 1, 0);
    // update(1, n, 0);
    t[0] = 1;
    rep(i, 1, m) {
        int delta = (t[i] - t[i - 1]) * d;
        int l = 1, r = 0;
        rep(j, 1, 1 + delta) h[++r] = j;
        rep(j, 1, n) {
            int L = max(1ll, j - delta);
            int R = min(n, j + delta);
            while (r >= l && h[l] < L) l++;
            while (r >= l && R != h[r] && p[R] >= p[h[r]]) r--;
            if (r > l || R > h[r]) h[++r] = R;
            g[j] = p[h[l]] + b[i] * (abs(j - a[i]));
        }
        rep(j, 1, n) p[j] = g[j];
    }
    int ans = -inf;
    rep(j, 1, n) ans = max(ans, p[j]);
    print(ans);
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