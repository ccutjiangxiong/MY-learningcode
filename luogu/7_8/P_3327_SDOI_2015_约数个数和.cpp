#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    const int N = 50000;
    vector<int> mu(N + 1), primes;
    vector<bool> vis(N + 1);
    mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!vis[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (i * p > N) break;
            vis[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
    vector<int> prefixMu(N + 1);
    for (int i = 1; i <= N; ++i) {
        prefixMu[i] = prefixMu[i - 1] + mu[i];
    }

    vector<int> d(N + 1, 0);
    for (int i = 1; i <= N; ++i)
        for (int j = i; j <= N; j += i) d[j]++;
    vector<ll> Dsum(N + 1, 0);
    for (int i = 1; i <= N; ++i) Dsum[i] = Dsum[i - 1] + d[i];

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int lim = min(n, m);
        ll ans = 0;
        int l = 1;
        while (l <= lim) {
            int x = n / l;
            int y = m / l;
            int r1 = n / x;
            int r2 = m / y;
            int r = min({r1, r2, lim});
            int smu = prefixMu[r] - prefixMu[l - 1];
            ans += (ll)smu * Dsum[x] * Dsum[y];
            l = r + 1;
        }
        cout << ans << "\n";
    }
    return 0;
}   