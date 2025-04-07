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
vector<int> e[N];
int a[N], f[N], tag[N], fl[N];
int n, m;
void dfs(int u, int fa) {
    f[u] = fa;
    for (int v : e[u])
        if (v != fa) dfs(v, u);
}
int div(int x) {
    int ans = 0;
    if (fl[x]) a[x] = tag[x], fl[x] = tag[x] = 0;
    ans ^= a[x];
    for (int v : e[x])
        if (v != f[x]) ans ^= div(v);
    return ans;
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    rep(i, 1, m) {
        int mode;
        cin >> mode;
        if (mode == 1) {
            int x, y;
            cin >> x >> y;
            tag[x] = y;
            fl[x] = 1;
        } else {
            int x;
            cin >> x;
            cout << div(x) << endl;
        }
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