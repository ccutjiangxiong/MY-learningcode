#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    for (long long t = 1; t <= n; t++) {
        // S = sum_{i=1..t-1} floor(i * n / t)
        long long g = std::gcd(n, t);
        long long S = ((n - 1) * (t - 1) + (g - 1)) / 2;
        if (S + n <= k * t) {
            cout << t << "\n";
            return 0;
        }
    }

    cout << "Poor E.S.! \n";
    return 0;
}