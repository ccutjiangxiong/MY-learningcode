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
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
#define lc p << 1
#define rc (p << 1 | 1)
struct Node {
    int l, r, sum, la, mi, ma;
} tr[N * 4];
int w[N];
set<int> s[N];
inline int &la(int a) { return tr[a].la; }
inline int &sum(int a) { return tr[a].sum; }
inline int &l(int a) { return tr[a].l; }
inline int &r(int a) { return tr[a].r; }
void pushup(int p) {
    sum(p) = sum(rc) + sum(lc);
    la(p) = min(la(rc), la(lc));
    tr[p].mi = min(tr[lc].mi, tr[rc].mi);
    tr[p].ma = min(tr[lc].ma, tr[rc].ma);
}
void build(int p, int l, int r) {
    tr[p] = {l, r, w[l], l, inf, 0};
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    pushup(p);
}
void update(int p, int x, int k) {
    if (x <= l(p) && x >= r(p)) {
        tr[p].mi = tr[p].ma = sum(p) = k;
        tr[p].la = x;
        if (*s[k].begin() < x) {
            tr[p].la = *(s[k].lowwer_bound(x) - 1);
        }
        return;
    }
    int m = (l(p) + r(p)) >> 1;
    if (x <= m) update(lc, x, k);
    if (x > m) update(rc, x, k);
    pushup(p);
}
piii query(int p, int x) {
    if (x <= l(p) && y >= r(p)) return {tr[p].mi, tr[p].ma, tr[p].la};
    int m = (l(p) + r(p)) >> 1;
    if (x <= m) return query(lc, x, y);
    if (y > m) return query(rc, x, y);
}
int ti = 1;

void work() {}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}