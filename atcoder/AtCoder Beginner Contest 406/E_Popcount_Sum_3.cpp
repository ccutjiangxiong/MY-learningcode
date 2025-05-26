#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
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
const int N = 2e6 + 5, mod = 998244353, inf = 1e18 + 3;
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

int ti, n, k;

int  C[60 + 1][60 + 1], pw2[60 + 1];
void init_comb() {
    for (int i = 0; i <= 60; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    pw2[0] = 1;
    for (int i = 1; i <= 60; i++) pw2[i] = pw2[i - 1] * 2 % mod;
}
int ff[66][66], h[N];
bitset<60> p;
int ans = 0, l;
int dfs(int x, int li, int cnt, int cur) {
    if (!li && ff[n - x + 1][k - cnt] >= 0) return cur+ff[n - x + 1][k - cnt];
    
    if(x==l+1&&cnt==k) return (cur);
    if (x > l && cnt > k) return 0;
    int y = li ? p[x - 1] : 1;
    int ans = 0;
    rep(i, 0, y) {
        int a = cur + (i << (l - 1 - x));
        ans += dfs(x + 1, li && x == p[x - 1], cnt + i, a);
    }
    ans %= mod;
    if (li == 0) ff[n - x + 1][k - cnt] = ans;
    return ans;
}
void work() {
    cin >> n >> k;
    p = n;
    ans = 0;
    l = bitl(n);
    me(ff, -1);
    dfs(1, 1, 0,0);
    h[0] = n;
    rep(i, 1, n) h[i] -= n & (1 << (i - 1));
    print(ans, ff[3][3]);
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