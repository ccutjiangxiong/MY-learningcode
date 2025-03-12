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
double x[N], r[N];
queue<int> q;
double ans[N];

void work() {
    cin >> n;
    rep(i, 1, n) ans[i] = mod;
    rep(i, 1, n) cin >> x[i] >> r[i];
    ans[1] = r[1];
    rep(i, 2, n) rep(j, 1, i - 1) {
        ans[i] = min({ans[i], (x[i] - x[j]) * (x[i] - x[j]) / 4 / ans[j], r[i]});
    }
    rep(i, 1, n) cout << ans[i] << endl;
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