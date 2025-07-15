#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> a, b;
vector<int> lg2;
vector<vector<int>> stMax, stMin;

void build() {
    lg2.resize(n + 1);
    lg2[1] = 0;
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i / 2] + 1;
    int K = lg2[n] + 1;
    stMax.assign(K, vector<int>(n));
    stMin.assign(K, vector<int>(n));
    for (int i = 0; i < n; i++) {
        stMax[0][i] = a[i];
        stMin[0][i] = b[i];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            stMax[k][i] = max(stMax[k - 1][i], stMax[k - 1][i + (1 << (k - 1))]);
            stMin[k][i] = min(stMin[k - 1][i], stMin[k - 1][i + (1 << (k - 1))]);
        }
    }
}

int queryMax(int l, int r) {
    int len = r - l + 1;
    int k = lg2[len];
    return max(stMax[k][l], stMax[k][r - (1 << k) + 1]);
}

int queryMin(int l, int r) {
    int len = r - l + 1;
    int k = lg2[len];
    return min(stMin[k][l], stMin[k][r - (1 << k) + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    build();

    ll ans = 0;
    for (int l = 0; l < n; l++) {
        int lo = l - 1, hi = n;
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            if (queryMax(l, mid) > queryMin(l, mid))
                hi = mid;
            else
                lo = mid;
        }
        int r1 = hi;
        lo = l - 1;
        hi = n;
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            if (queryMax(l, mid) >= queryMin(l, mid))
                hi = mid;
            else
                lo = mid;
        }
        int r2 = hi;

        if (r2 < r1) ans += (r1 - r2);
    }

    cout << ans << "\n";
    return 0;
}