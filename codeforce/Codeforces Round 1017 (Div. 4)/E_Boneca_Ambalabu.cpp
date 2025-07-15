#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        long long fre[30] = {0};
        for (int i = 0; i < n; ++i) {
            for (int b = 0; b < 30; ++b) {
                if (a[i] & (1 << b)) {
                    fre[b]++;
                }
            }
        }
        long long max_sum = 0;
        for (int k = 0; k < n; ++k) {
            long long _sum = 0;
            for (int b = 0; b < 30; ++b) {
                if (a[k] & (1 << b)) {
                    _sum += (n - fre[b]) * (1LL << b);
                } else {
                    _sum += fre[b] * (1LL << b);
                }
            }
            max_sum = max(max_sum, _sum);
        }

        cout << max_sum << "\n";
    }

    return 0;
}