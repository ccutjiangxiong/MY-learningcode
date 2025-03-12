#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n, l;
int f[N], dp[N], pre[N];
int x[N], y[N];
int q[N], cnt;
int fun(int x) { return x * x; }

int slope(int u, int v) { return x[u] == x[v] ? 0 : (y[u] - y[v]) / (x[u] - x[v]); }
void work() {
    cin >> n >> l;
    rep(i, 1, n) cin >> f[i];
    rep(i, 1, n) f[i]++;
    rep(i, 1, n) dp[i] = inf, pre[i] = pre[i - 1] + f[i];
    dp[0] = 0;
    l++;
    q[++cnt] = 0;
    dp[0] = 0;
    // rep(i, 1, n) {
    //     rep(j, 0, i - 1) {
    //         dp[i] = min(dp[i], dp[j] + fun(pre[i] - pre[j] - l));
    //         rep(i, 1, n) std::cout << (dp[i]) << ' ';
    //         std::cout << std::endl;
    //     }
    //     // rep(j, 0, i - 1) cout << j << ' ';
    //     cout << endl;
    // }
    rep(i, 1, n) std::cout << (dp[i]) << ' ';
    std::cout << std::endl ;
    print(dp[n]);
    rep(i, 1, n) dp[i] = inf;
    rep(i, 1, n) {
        rep(j, 1, cnt) {
            // std::cout << (q[cnt] == j - 1) << "            D!!!!!!!!!!!\n";
            print(j,q[cnt]);
            // dp[i] = min(dp[i], dp[q[cnt]] + fun(pre[i] - pre[q[cnt]] - l));
            // rep(i, 1, n) std::cout << (dp[i]) << ' ';
            // std::cout << std::endl;
        }

        // rep(j, 1, cnt) cout << q[j] << ' ';
        // y[i] = dp[i] + 2 * pre[i] * l + pre[i] * pre[i];
        // x[i] = 2 * pre[i];
        // while (cnt > 2 && slope(i, q[cnt - 1]) > slope(q[cnt-1], q[cnt])) cnt--;
        q[++cnt] = i;
        cout << endl;
    }
    rep(i, 1, n) std::cout << (dp[i]) << ' ';
    std:: cout  << std::endl;
    print(dp[n]);
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