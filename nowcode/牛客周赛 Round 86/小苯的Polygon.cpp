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
int ti;
int n, a[N];
int ans = inf;
int pre[N];
map<piii, int> mp;
void dfs(int x, int su, int v) {
    if (su > ans || x > n || mp[{x, su, v}]) return;
    mp[{x, su, v}] = 1;
    if (a[x] < su && v >= 2) ans = min(ans, su + a[x]);
    dfs(x + 1, su + a[x], min(v + 1, 2ll));
    dfs(x + 1, su, v);
}
void work() {
    ans = inf;
    cin >> n;
    mp.clear();
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) pre[i] = 0;
    sort(a + 1, a + 1 + n);
    rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
    dfs(1, 0, 0);
    if (ans == inf)
        cout << -1 << endl;
    else
        cout << ans << endl;
    // rem(i, n, 3) if (a[i] < pre[i - 1]) ans = max(a[i] + pre[i - 1], ans);
    // cout << ans << endl;
    // rep(i,1,n) if(a[i]<)
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