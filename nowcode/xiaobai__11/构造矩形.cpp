#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N   = 2e6 + 5;
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
int f[N], g[N], h[N];
void work() {
    cin >> n >> m >> k;
    int ans = 0;
    rep(l, 1, max(n, m)) {
        g[l] += max(0ll, m - (l + k) + 1);
        if (l > k) g[l] += max(0ll, m - (l - k) + 1);
    }
    rep(i, 1, n) cin >> f[i];
    sort(f + 1, f + 1 + n);

    rep(i, 1, n) rep(j, i + 1, n) {
        ans += g[f[j] - f[i]];
        // print(i, j, x);
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