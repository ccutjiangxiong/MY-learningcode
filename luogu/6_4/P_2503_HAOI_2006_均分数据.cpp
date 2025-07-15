#include <bits/stdc++.h>
#include <setjmp.h>

#include <random>

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
int ti = 1, n, m, k, a[N], b[N], c[N];
ld ans, res, cnt, x, y, z;
vi e[N];
ld cal(int m) {
    ld sum = 0;
    rep(i, 1, m) sum += (c[i] - x) * (c[i] - x);
    return sqrt(sum / m);
}
void sa() {
    auto st = clock();
    uniform_int_distribution<int> dx(1, n), dy(1, m);
    while (1) {
        if ((double)(clock() - st) / CLOCKS_PER_SEC > 0.9) break;
        int x = dx(rng), y = dy(rng);
        if (b[x] == y) continue;
        int cur = b[x];
        c[cur] -= a[x];
        b[x] = y;
        c[y] += a[x];
        ld ne = cal(m);
        ans = min({ans, ne, res});
        if (ne < res || 0.1 > ranf(0.0, 1))
            res = ne;
        else {
            c[cur] += a[x];
            c[y] -= a[x];
            b[x] = cur;
        }
    }
}

void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i], b[i] = 1, c[1] += a[i];
    x = c[1] * 1.0 / m;
    ans = res = cal(m);
    sa();
    cout << format("{:.2f}", ans);
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