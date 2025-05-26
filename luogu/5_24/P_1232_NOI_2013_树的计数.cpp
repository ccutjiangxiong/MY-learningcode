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

int ti = 1, n, a[N], x, b[N], sum[N], dfn[N], pos[N];
void mark(int x, int y) { sum[x]++, sum[y + 1]--; }
void work() {
    cin >> n;
    ld ans = 1;
    mark(1, 1);
    rep(i, 1, n) { dfn[(cin >> x, x)] = i; }
    rep(i, 1, n) { pos[dfn[(cin >> x, x)]] = i; }
    rep(i, 1, n) dfn[pos[i]] = i;
    rep(i, 1, n - 1) {
        if (dfn[i] > dfn[i + 1]) ans++, mark(i, i);
        if (pos[i] < pos[i + 1] - 1) mark(pos[i], pos[i + 1] - 1);
    }
    int now = 0;
    rep(i, 1, n - 1) now += sum[i], ans += (now ? 0 : 0.5);
    ans += 1;
    cout << format("{:.3f}", ans) << endl;
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