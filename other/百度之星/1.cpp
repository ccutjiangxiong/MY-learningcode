#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--);

using namespace std;
using ld = long double;
using vi = vector<int>;
int ti;
const int mod = 998244353, N = 2e5 + 5;
vi e[N];
int ans = 1;
void dfs(int u, int fa) {
    if (e[u].size() > 1) {
        ans *= e[u].size() - 1;
    }
    for (int v : e[u])
        if (v != fa) dfs(v, u);
}
void work() {
    int n;
    cin >> n;
    ans = 1;
    vi a(n + 11);
    rep(i, 1, n - 1) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    rep(i, 1, n) {
        if (e[i].size() == 1) dfs(i, 0);
        break;
    }
    rep(i, 1, n) e[i].clear();
    cout << ans << endl;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}
