#include <bits/stdc++.h>

using namespace std;
using LL = long long;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<LL> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    LL minv = *min_element(a.begin(), a.end());
    LL maxv = *max_element(a.begin(), a.end());
    if (k == n) {
        if (minv != maxv)
            cout << -1 << "\n";
        else
            cout << 0 << "\n";

        return;
    }

    LL sum = accumulate(a.begin(), a.end(), 0LL);
    LL x = (sum - k * maxv) / (n - k);
    while ((n - k) * x > sum - k * maxv) x--;
    while ((n - k) * (x + 1) <= sum - k * maxv) x++;
    x = min(x, minv);

    LL ans = -1;
    for (LL i = x; i >= x - k; i--)
        if ((sum - n * i) % k == 0) {
            ans = (sum - n * i) / k;
            break;
        }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;

    while (T--) solve();

    return 0;
}