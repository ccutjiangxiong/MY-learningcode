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
vector<int> q;
double ans[N], u[N],y[N];
double slope(int i, int j) {
    return u[i]==u[j]?1e-9:(y[j]-y[i])/(u[j]-u[i]);
}
void work() {
    cin >> n;
    rep(i, 1, n) ans[i] =r[i];
    rep(i, 1, n) cin >> x[i] >> r[i];
    rep(i, 1, n) {
        for (int p : q) ans[i] = min(ans[i], (x[i] - x[p]) * (x[i] - x[p]) / 4 / ans[p]);
        // x[i]=
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