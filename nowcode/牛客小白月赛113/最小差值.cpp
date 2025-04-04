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
int n, m;
int a[N], b[N], c[N];
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, m) cin >> b[i];
    rep(i, 1, n) c[i] = a[i];
    rep(i, 1, m) c[n + i] = b[i];
    sort(c + 1, c + 1 + n + m);
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + m);
    a[0]=b[0]=c[0] = -2000000000;
    c[1 + n + m] = 2000000000;
    int sua = 0, sub = 0;
    int x = c[0];
    rep(i, 1, n) sua += a[i]-x;
    rep(i, 1, m) sub += b[i] - x;
    int j = 0, k = 0;
    int sum = abs(sua - sub), ans = -2000000000;
    rep(i, 0, n + m+1) {
        sua += (2 * j - n) * (c[i] - c[i - 1]);
        sub += (2 * k - m) * (c[i] - c[i - 1]);
        while (c[i] == a[j + 1]) j++;
        while (c[i] == b[k + 1]) k++;
        if (abs(sua - sub) < sum) sum = sua - sub, ans = c[i];
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