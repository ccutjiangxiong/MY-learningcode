#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int x, n;
int f[N], g[N];
void work() {
    cin >> x;
    f[0] = 1;
    rep(i, 1, 2e5) g[i] = g[i - 1] + i;
    rep(i, 1, 2e5) f[i] = i;
    int k = 1;
    while (g[k + 1] <= x) k++;
    if (g[k] == x) {
        print(k + 1);
        rem(i, k + 1, 1) cout << i << ' ';
    } else {
        int y = x - g[k] + 1;
        int z = 0;
        while ((z + 1) * 2 <= min(2 * y - 2, k + 1) && (k - z + 1) >= y) z++;
        print(k + 2);
        cout << y << ' ';
        rem(j, k + 1 - z, z + 1) cout << j << ' ';
        rem(i, z, 1) cout << i << ' ' << i << ' ';
    }
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