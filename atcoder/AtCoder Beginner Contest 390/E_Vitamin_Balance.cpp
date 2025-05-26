#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005;
int n, x;
int v[N], a[N], c[N];
ll dp1[N], dp2[N], dp3[N];
void solve(ll *dp, int op) {
    for (int i = 1; i <= n; ++i) {
        if (v[i] != op) continue;
        for (int j = x; j >= c[i]; --j) dp[j] = max(dp[j], dp[j - c[i]] + a[i]);
    }
}
int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &v[i], &a[i], &c[i]);
    solve(dp1, 1);
    solve(dp2, 2);
    solve(dp3, 3);
    ll ans = 0;
    for (int i = 1; i <= x; ++i)
        for (int j = 1; j <= x - i; ++j) {
            int k = x - i - j;
            ans = max(ans, min(min(dp1[i], dp2[j]), dp3[k]));
        }
    printf("%lld\n", ans);
}