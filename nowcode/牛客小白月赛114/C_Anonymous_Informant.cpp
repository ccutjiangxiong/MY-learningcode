#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    k = min(k, n);
    int last = n - 1;
    for (int _ = 0; _ < k; _++) {
        if (a[last] > n) {
            cout << "No\n";
            return;
        }
        last += n - a[last];
        if (last >= n) {
            last -= n;
        }
    }
    cout << "Yes\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}