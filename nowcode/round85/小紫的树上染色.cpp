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
int n, k;
vector<int> e[N];
int cnt = 0;
int dfs(int u, int fa, int li) {
    int ans = 1;
    for (int v : e[u])
        if (v != fa) ans += dfs(v, u, li);
    if (ans > li) cnt++, ans = 0;
    // print(u, ans, li, cnt);
    return ans;
}
bool check(int x) {
    cnt = 0;
    dfs(1, 0, x);
    // print(cnt, x);
    return cnt <= k;
}
void work() {
    cin >> n >> k;
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int l = 0, r = n;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
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