#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 20;
const ll MOD = 998244353;
ll mod_add(ll a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
ll mod_mul(ll a, ll b) { return (a % MOD) * (b % MOD) % MOD; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    static int A[MAXN][MAXN];
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        A[u][v]++;
        A[v][u]++;
    }

    ll ans = 0;
    // count 2-cycles from multi-edges
    for (int u = 0; u < N; u++) {
        for (int v = u + 1; v < N; v++) {
            if (A[u][v] >= 2) {
                ll cnt = A[u][v];
                ans = mod_add(ans, cnt * (cnt - 1) / 2 % MOD);
            }
        }
    }

    // count cycles of length >=3
    for (int s = 0; s < N; s++) {
        int H = N - s - 1;
        if (H < 2) continue;
        vector<int> tos;
        tos.reserve(H);
        for (int v = s + 1; v < N; v++) tos.push_back(v);
        int m = tos.size();
        int SZ = 1 << m;
        // dp[mask][last]: ways to go from s -> tos[last] visiting mask (includes last)
        vector<ll> dp(SZ * m, 0);
        // init paths of length 1
        for (int j = 0; j < m; j++) {
            int v = tos[j];
            if (A[s][v] > 0) {
                dp[(1 << j) * m + j] = A[s][v];
            }
        }
        for (int mask = 1; mask < SZ; mask++) {
            int bcnt = __builtin_popcount(mask);
            if (bcnt < 1) continue;
            int lb = __builtin_ctz(mask);
            for (int last = 0; last < m; last++) {
                if (!(mask & (1 << last))) continue;
                ll ways = dp[mask * m + last];
                if (!ways) continue;
                int u = tos[last];
                // extend path
                for (int nxt = last + 1; nxt < m; nxt++) {
                    if (mask & (1 << nxt)) continue;
                    int v = tos[nxt];
                    if (A[u][v] > 0) {
                        ll &d = dp[((mask | (1 << nxt)) * m) + nxt];
                        d = mod_add(d, mod_mul(ways, A[u][v]));
                    }
                }
                // close cycle
                if (bcnt >= 2 && A[u][s] > 0) {
                    // only count if first visited (lb) < last to avoid reverse dup
                    if (lb < last) {
                        ans = mod_add(ans, mod_mul(ways, A[u][s]));
                    }
                }
            }
        }
    }

    cout << ans % MOD << "\n";
    return 0;
}