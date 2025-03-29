#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 3e3 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti;

struct State {
    int diff, mn, mx;
};
State dp[3001][3001];
int a[N], pre[N], ans[N];
void work() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = {0LL, 0LL, 0LL};
        }
    }

    for (int i = 1; i <= n; i++) {
        int sy = pre[i] - pre[0];
        dp[i][1] = {0LL, sy, sy};
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= i; j++) {
            int bd = -1;
            int bm = 0, bmx = 0;
            for (int t = j - 1; t < i; t++) {
                int sy = pre[i] - pre[t];
                auto &prev = dp[t][j - 1];
                int mbn = min(prev.mn, sy);
                int nx = max(prev.mx, sy);
                int nd = nx - mbn;
                if (nd > bd) {
                    bd = nd;
                    bm = mbn;
                    bmx = nx;
                }
            }
            dp[i][j] = {bd, bm, bmx};
        }
    }

    //     vector<int> ans(n);
    for (int k = 0; k < n; k++) {
        ans[k] = dp[n][n - k].diff;
    }
    for (auto &x : ans) cout << x << " ";
    cout << "\n";
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