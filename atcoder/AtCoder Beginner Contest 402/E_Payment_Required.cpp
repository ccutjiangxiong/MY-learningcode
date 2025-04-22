#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

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
// ld dp[1111][111];
void work() {
    int N, X;
    cin >> N >> X;
    vector<int> S(N), C(N);
    vector<ld> P(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> S[i] >> C[i] >> x;
        P[i] = (ld)x / 100.0;
    }
    int M = 1 << N;
    vector<vector<ld>> dp(M, vector<ld>(X + 1, 0.0L));
    for (int s = X; s >= 0; --s) {
        for (int m = 0; m < M; ++m) {
            ld b = 0.0L;
            for (int i = 0; i < N; ++i) {
                if (!(m & (1 << i)) && s + C[i] <= X) {
                    ld p = P[i];
                    ld w = S[i] + dp[m | (1 << i)][s + C[i]];
                    ld lo = dp[m][s + C[i]];
                    b = max(b, p * w + (1 - p) * lo);
                }
            }
            dp[m][s] = b;
        }
    }
    printf("%Lf", dp[0][0]);
    // cout << format("{:.10f}", dp[0][0]) << "\n";
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