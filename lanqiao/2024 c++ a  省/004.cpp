#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const long double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n, k, t, a[N], b[N];
int pre[N], pre2[N];
long double fun(int x) {
    rep(i, 1, x) b[i] = a[i];
    sort(b + 1, b + 1 + x);
    long double ans = inf;
    rep(i, 1, x) pre[i] = pre[i - 1] + b[i];
    rep(i, 1, x) pre2[i] = pre2[i - 1] + b[i] * b[i];
    rep(i, k, x) {
        long double ave = (pre[i] - pre[i - k]) * 1.0 / k;
        long double y = ave * ave * k + pre2[i] - pre2[i - k];
        y-=2*ave*(pre[i]-pre[i-k]);
        y /= k;
        ans = min(ans, y);
    }
    return ans;
}
void work() {
    cin >> n >> k >> t;
    rep(i, 1, n) cin >> a[i];
    int l = 1, r = n;
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (fun(mid) <= t)
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
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