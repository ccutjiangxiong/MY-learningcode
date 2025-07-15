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

int ti, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];

void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> b[i];
    ans = 0;
    rep(i, 1, n) if (i & 1) swap(a[i], b[i]);
    set<int> s1, s2, s3;
    rem(i, n, 1) {
        if (i > 1) {
            int f1 = 0, f2 = 0, f3 = 0, f4 = 0;
            if (!s1.contains(b[i - 1])) f1 = 1, s1.ep(b[i - 1]);
            if (!s2.contains(a[i - 1])) f2 = 1, s2.ep(a[i - 1]);
            if (!s3.contains(b[i - 1])) f3 = 1, s3.ep(b[i - 1]);
            if (!s3.contains(a[i - 1])) f4 = 1, s3.ep(a[i - 1]);
            if (sz(s1) + sz(s2) != sz(s3)) ans = max(ans, i - 1);
            if (f1) s1.erase(b[i - 1]);
            if (f2) s2.erase(a[i - 1]);
            if (f3) s3.erase(b[i - 1]);
            if (f4) s3.erase(a[i - 1]);
        }
        s1.ep(a[i]);
        s2.ep(b[i]), s3.ep(a[i]), s3.ep(b[i]);
        if (sz(s1) + sz(s2) != sz(s3)) {
            ans = max(ans, i);
            break;
        }
    }
    pt(ans);
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