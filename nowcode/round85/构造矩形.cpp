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
int n, m, k;
int f[N], pre[N];
void work() {
    cin >> n >> m >> k;
    int ans = 0;
    rep(i, 1, n) cin >> f[i];
    sort(f + 1, f + 1 + n);
    int g = 1, p = 1;
    rep(i, 1, n) pre[i] = pre[i - 1] + f[i];

    rep(i, 2, n) {
        while (f[g] - f[i] + k > m + 1) g++;
        ans += (i-g) * (m + 1) + pre[i] - pre[g] - k * (i - g);
        while (f[p] - f[i] <= k) p++;
        ans += (i-p) * (m + 1) + pre[i] - pre[p] + k * (i - p);
    }

    cout << ans << endl;
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