#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
int n;
int a[N], b[N];
int ans = 0;
void work() {
    cin >> n;
    rep(i, 1, 2 * n) cin >> a[i];
    rep(i, 1, 2 * n) cin >> b[i];
    rep(i, 1, n) b[i] = a[i] % 3 + 1;
    rep(i, n + 1, 2 * n) a[i] = (b[i] - 1);
    rep(i, n + 1, 2 * n) if (a[i] == 0) a[i] = 3;
    cout << 2 * n << endl;
    rep(i, 1, 2 * n) cout << a[i] << ' ';
    cout << endl;
    rep(i, 1, 2 * n) cout << b[i] << ' ';
    cout << endl;
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