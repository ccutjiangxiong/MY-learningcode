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
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];
int cal(int yy, viii &nf, viii &f, int mo) {
    int cur = 0, rr = -inf;
    for (auto [x, y, m] : f) {
        if (y + m <= yy) continue;
        if (mo) nf.pb(x, y, m);
        int cx = x + (m - (yy - y));
        if (x >= rr)
            cur += (cx - x), rr = cx;
        else if (cx > rr)
            cur += (cx - rr), rr = cx;
    }
    return cur;
}
int get_y(int x1, int y1, int m1, int h, int yy, int m2) {
    int y = y1 - (h - x1);
    if (yy - y <= m2 && yy - y > 0 && (y1 - y <= m1 && y1 - y)) return y;
    return -inf;
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i] >> b[i] >> c[i];
    vi g;
    viii ss;
    rep(i, 1, n) g.pb(b[i]), g.pb(b[i] + c[i]);
    rep(i, 1, n) ss.pb(b[i], a[i], c[i]);
    rep(i, 1, n) rep(j, 1, n) if (i != j) {
        int a1 = get_y(a[i], b[i] + c[i], c[i], a[j], b[j] + c[j], c[j]);
        int a2 = get_y(a[j], b[j] + c[j], c[j], a[i], b[i] + c[i], c[i]);
        if (a1 != -inf) g.pb(a1);
        if (a2 != inf) g.pb(a2);
    }
    rg::sort(ss);
    rg::sort(g);
    g.erase(unique(all(g)), g.end());
    ld ans = 0;
    int la = -1;
    viii f;
    rep(i, 1, sz(g)) {
        int yy = g[i - 1];
        viii nf;
        int cur = cal(yy, nf, f, 0);
        if (la != -1) ans += (cur + la) * (g[i - 1] - g[i - 2]) / 2.0;
        while (cnt < sz(ss) && yy >= get<0>(ss[cnt])) {
            auto [y, x, m] = ss[cnt++];
            f.pb(x, y, m);
        }
        rg::sort(f);
        cur = cal(yy, nf, f, 1);
        f = nf;
        la = cur;
    }
    cout << format("{:.1f}", ans);
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