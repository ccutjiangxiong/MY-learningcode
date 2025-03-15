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
int n, m;
int ans;
vector<int> e[1111];
void work() {
    cin >> n;
    int m = (n - 1) * n / 2;
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(w);
        e[v].push_back(w);
    }
    rep(i, 1, n) sort(e[i].begin(), e[i].end());
    rep(i, 1, n) for (int j = 1; j <= n - 1; j += 2) ans += e[i][j];
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