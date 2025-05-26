#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

using namespace std;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18;

int ti = 1, n, m, x, y, a[N], b[N], c[N];
template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << '\n';
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i] >> b[i] >> c[i];
    rep(i, 1, n) {
        int u = 0, v = 0;

        rep(j, 1, n) if (i != j) {
            if (a[j] < a[i] && b[i] >= c[j]) u = j;
            if (a[j] < a[i] && c[i] <= b[i]) v = j;
            pt(u, v);
        }
    }
}
signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    if (!ti) cin >> ti;

    while (ti--) work();
}
