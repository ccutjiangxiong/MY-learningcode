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

int ti=1,n,m,s,t;
int dp[2001][2001],gr[2222][2222];
int suf[2001][2001];
void work() {
    cin >> n >> m >> s >> t;

    rep(i, 1, n) rep(j, 1, m) cin >> gr[i][j];

    rep(j, 1, m) {
        suf[n + 1][j] = 0;
        rem(i, n, 1) suf[i][j] = suf[i + 1][j] + gr[i][j];
    }
  
    rep(i, 1, n) rep(j, 1, m) dp[i][j] = -inf;
    dp[s][1] = gr[s][1];


    vector<int> A(n + 2), B(n + 2), pre(n + 2), sufMx(n + 3);


    rep(j, 1, m) {
        int s1 = suf[1][j];

        rep(i, 1, n) A[i] = dp[i][j] + suf[i + 1][j];
        pre[1] = A[1];
        rep(i, 2, n) pre[i] = max(pre[i - 1], A[i]);
        B[n] = dp[n][j] + suf[n + 1][j] + s1;
        sufMx[n] = B[n];
        rem(i, n - 1, 1) {
            B[i] = dp[i][j] + suf[i + 1][j] + s1;
            sufMx[i] = max(sufMx[i + 1], B[i]);
        }
        rep(i, 1, n) {
            int best = pre[i];
            if (i < n) best = max(best, sufMx[i + 1]);
            dp[i][j] = best - suf[i + 1][j];
        }
        if (j < m) {
            rep(i, 1, n) dp[i][j + 1] = dp[i][j] + gr[i][j + 1];
        }
    }
    cout << dp[t][m] << "\n";
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