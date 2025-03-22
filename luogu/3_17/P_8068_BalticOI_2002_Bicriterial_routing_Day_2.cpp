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
int n, m, s, e;

vector<pii> ee[N];
pii dp[N], f[N];
vector<pii> g[N];
int cnt = 0;
int vis[N];
void dfs(int u, int t) {
    for (auto {x, y} : ee[u]) {
        if (vis[x]) {
        } else {
            rep(auto {p,q} : g[u]) g[x].empalc_back()
        }
    }
}
void work() {
    cin >> n >> m >> s >> e;
    rep(i, 1, m) {
        int p, r, c, t;
        cin >> p >> r >> c >> t;
        f[++cnt] = {c, t};
        ee[p].emplace_back(r, cnt);
        ee[r].emplace_back(t, cnt);
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