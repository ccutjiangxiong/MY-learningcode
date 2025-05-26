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

int ti;
int n, a[N], pos[N], pre[N], nxt[N], ans;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n + 1) pos[i] = 0;
    rep(i, 1, n) {
        pre[i] = max(pos[a[i]], pos[a[i] + 1]);
        pos[a[i]] = i;
    }
    rep(i, 1, n + 1) pos[i] = n + 1;
    rem(i, n, 1) {
        nxt[i] = pos[a[i] + 1];
        pos[a[i]] = i;
    }
    rep(i, 1, n) ans += (nxt[i] - i) * (i - pre[i]);
    cout << ans << endl;
    return 0;
}
