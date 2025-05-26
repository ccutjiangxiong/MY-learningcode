#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a);
#define cnt1(a) __builtin_popcount(a);
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


int ti = 1;  
int n;
int a[505][505];
void work() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) cin >> a[i][j];

    const int MOD = 1000000007;
    int T = (n - 1) / 2;
    static int dp[505][505], ndp[505][505];
    memset(dp, 0, sizeof(dp));
    for (int c2 = 1; c2 <= n; c2++) {
        if (a[1][1] == a[n][c2]) dp[1][c2] = 1;
    }
    for (int step = 1; step <= T; step++) {
        int r1 = step, r2 = n - step + 1;
        int nr1 = r1 + 1, nr2 = r2 - 1;
        memset(ndp, 0, sizeof(ndp));
        for (int c1 = 1; c1 <= r1; c1++) {
            for (int c2 = 1; c2 <= r2; c2++) {
                int fjdslf = dp[c1][c2];
                if (!fjdslf) continue;
                for (int d1 = 0; d1 <= 1; d1++) {
                    int nc1 = c1 + d1;
                    if (nc1 < 1 || nc1 > nr1) continue;
                    for (int d2 = 0; d2 <= 1; d2++) {
                        int nc2 = c2 - d2;
                        if (nc2 < 1 || nc2 > nr2) continue;
                        if (a[nr1][nc1] != a[nr2][nc2]) continue;
                        ndp[nc1][nc2] = (ndp[nc1][nc2] + fjdslf) % MOD;
                    }
                }
            }
        }
        memcpy(dp, ndp, sizeof(dp));
    }
    long long ans = 0;
    int r1 = T + 1, r2 = n - T;
    if (r1 == r2) {
        for (int c = 1; c <= r1; c++) ans = (ans + dp[c][c]) % MOD;
    } else {
        for (int c1 = 1; c1 <= r1; c1++) {
            for (int dc = 0; dc <= 1; dc++) {
                int c2 = c1 + dc;
                if (c2 >= 1 && c2 <= r2) ans = (ans + dp[c1][c2]) % MOD;
            }
        }
    }
    print(ans);
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