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
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;

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

int ti=1 ,n,m,k,a[N],b[N],c[N],ans,res,cnt,x,y,z;
vi e[N];
#define lc p << 1
#define rc (p << 1 | 1)
struct Node {
    int l, r, sum, add;
} tr[N * 4];
int w[N];
inline int &sum(int a) { return tr[a].sum; }
inline int &add(int a) { return tr[a].add; }
inline int &l(int a) { return tr[a].l; }
inline int &r(int a) { return tr[a].r; }
void pushup(int p) { sum(p) = sum(rc) + sum(lc); }
void build(int p, int l, int r) {
    tr[p] = {l, r, w[l], 0};
    if (l == r)
        return;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    pushup(p);
}
void pushdown(int p) {
    if (add(p)) {
        sum(lc) += add(p) * (r(lc) - l(lc) + 1);
        sum(rc) += add(p) * (r(rc) - l(rc) + 1);
        add(lc) += add(p);
        add(rc) += add(p);
        add(p) = 0;
    }
}
void update(int p, int x, int y, int k) {
    if (x <= l(p) && y >= r(p)) {
        sum(p) += (r(p) - l(p) + 1) * k;
        add(p) += k;
        return;
    }
    int m = (l(p) + r(p)) >> 1;
    pushdown(p);
    if (x <= m)
        update(lc, x, y, k);
    if (y > m)
        update(rc, x, y, k);
    pushup(p);
}
int query(int p, int x, int y) {
    if (x <= l(p) && y >= r(p))
        return sum(p);
    int m = (l(p) + r(p)) >> 1;
    pushdown(p);
    int sum = 0;
    if (x <= m)
        sum += query(lc, x, y);
    if (y > m)
        sum += query(rc, x, y);
    return sum;
}
void work() {
    cin >> n;
    rep(i, 1, n) {
        cin >> x >> y >> z;
        
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}