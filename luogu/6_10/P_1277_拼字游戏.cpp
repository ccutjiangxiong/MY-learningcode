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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
vi e[N];
int gr[5][5], tt[5][5];
int rr[11], cc[11], dd[11];
viii g;
bool dfs(int k) {
    if (k == g.size()) {
        rep(k, 1, 4) if (a[k] || b[k] || c[k]) return 0;
        return 1;
    }
    auto [w, i, j] = g[k];

    if (gr[i][j]) return dfs(k + 1);
    int mo = 0;
    if (i == j) mo = 1;
    if (i + j == 5) mo = 2;
    int up = min({a[i], b[j], c[mo]});
    int st = 1;
    if (rr[i] == 1 && a[i]) st = a[i];
    if (cc[j] == 1 && b[j]) {
        if (st != 1 && st != b[j]) return 0;
        st = b[j];
    }
    if (dd[mo] == 1 && c[mo]) {
        if (st != 1 && st != c[mo]) return 0;
        st = c[mo];
    }
    vi f(max(up - st + 1, 0ll));
    iota(all(f), st);
    shuffle(all(f), rng);
    for (int u : f) {
        a[i] -= u, b[j] -= u, c[mo] -= u;
        gr[i][j] = u;
        rr[i]--, cc[j]--, dd[mo]--;
        if (dfs(k + 1)) return 1;
        gr[i][j] = 0;
        rr[i]++, cc[j]++, dd[mo]++;
        a[i] += u, b[j] += u, c[mo] += u;
    }
    return 0;
}
void work() {
    n = 4;
    rep(i, 1, 4) cin >> a[i];
    rep(i, 1, 4) cin >> b[i];
    rep(i, 1, 2) cin >> c[i];
    dd[0] = c[0] = inf;
    rep(i, 1, 4) rr[i] = cc[i] = dd[i] = 4;
    rep(i, 1, 4) {
        cin >> x >> y >> z;
        x++, y++;
        gr[x][y] = z;
        rr[x]--, cc[y]--;
        a[x] -= z;
        b[y] -= z;
        if (x == y) c[1] -= z, dd[1]--;
        if (x + y == 5) c[2] -= z, dd[2]--;
    }
    rep(i, 1, 4) rep(j, 1, 4) {
        int mo = 0;
        if (x == y) mo = 1;
        if (x + y == 5) mo = 2;
        g.pb(min({a[i], b[j], c[mo]}), i, j);
    }
    rg::sort(g);
    dfs(0);
    rep(i, 1, n) rep(j, 1, n) cout << gr[i][j] << " \n"[j == n];
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