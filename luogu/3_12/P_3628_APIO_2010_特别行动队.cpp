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
int ti = 1;
int n;
int a, b, c, x[N];
int p[N], u[N], v[N];
int ha, st = 1, f[N], dp[N];
double slope(int x, int y) { return (v[y] - v[x]) * 1.0 / (u[y] - u[x]); }
void work() {
    cin >> n >> a >> b >> c;
    rep(i, 1, n) cin >> x[i];
    rep(i, 1, n) p[i] = p[i - 1] + x[i];
    f[++ha] = 0;
    rep(i, 1, n) {
        while (ha > st && slope(f[st], f[st + 1]) >- 2 * p[i]) st++;
        int xx = p[i] - p[f[st]];
        dp[i] = max(dp[i], dp[f[st]] + xx * a * xx + xx * b + c);
        v[i] = dp[i] + a * p[i] * p[i] - b * p[i];
        u[i] = p[i];
        while (ha > st && slope(f[ha - 1], f[ha]) >= slope(f[ha], i)) ha--;
        f[++ha] = i;
    }
    cout << dp[n] << endl;
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