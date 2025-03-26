#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
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
int n;
int f[N];
vector<int> e[N];
void work() {
    cin >> n;
    if (n == 1) {
        cout << 1 << ' ' << 1 << endl;
        return;
    }
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int ans = 0;
    rep(i, 1, n) ans = max(ans, (int)e[i].size());
    cout << ans - 1 << ' ';
    rep(i, 1, n) if (e[i].size() == 1) {
        cout << i << endl;
        break;
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