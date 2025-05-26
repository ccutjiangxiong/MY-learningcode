#include <bits/stdc++.h>

using namespace std;
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
void solve() {
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> a(n + 1), pre1(n + 1), pre2(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a.begin() + 1, a.end());
    for (int i = 1; i <= n; i++) {
        pre1[i] = pre1[i - 1] + a[i];
        pre2[i] = pre2[i - 1] + a[i] * a[i];
    }
    long double ans = 1.0e30l;
    for (int i = 0; i < n; i++) {
        // 枚举最后一棵被彻底砍掉的树
        if (pre1[i] > s) break;
        long long lst = s - pre1[i];
        int l = i + 1, r = n;
        while (l < r) {
            // 贪心 用二分找在贪心策略下最后一棵被砍过的树
            int mid = (l + r) >> 1;
            if ((n - mid) * a[mid] + lst <= pre1[n] - pre1[mid])
                l = mid + 1;
            else
                r = mid;
        }
        long long sq1 = pre2[l - 1] - pre2[i];        // 没被砍的树高平方和
        long long tot = pre1[n] - pre1[l - 1] - lst;  // 被砍过的树的总高度
        long long height = tot / (n - l + 1);         // 被砍过的树的最小高度
        long long sq2 = (height + 1) * (height + 1) * (tot % (n - l + 1)) +
                        height * height * ((n - l + 1) - tot % (n - l + 1));  // 被砍过的树高平方和
        long double ave_sq = (long double)(pre1[n] - s) * (pre1[n] - s) / (n - i) / (n - i);
        ans = min(ans, (long double)(sq1 + sq2) / (n - i) - ave_sq);
        print(i, (long double)(sq1 + sq2) / (n - i) - ave_sq);
    }
    cout << fixed << setprecision(6) << ans << '\n';
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
