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
int n, m, k;
int f[N];
vector<pii> e[N];
int ans = 0;
map<pii, int> mp;
int vis[N];
void dfs(int u, int s) {
    if (mp[{u, s}]) return;
    mp[{u, s}] = 1;
    int w = 0, b = 0;
    while (s >> b) w += (s >> b) & 1, b++;
    if (u == 1) ans = max(ans, w);
    int g = 0;
    rep(i, 1, k) if (f[i] == u) g = i;
    if (g && !(s & (1 << g))) dfs(u, s | (1 << g));
    for (auto [v, p] : e[u])
        if (w <= p) dfs(v, s);
}

void work() {
    cin >> n >> m >> k;
    rep(i, 1, k) cin >> f[i];
    rep(i, 1, m) {
        int x, y, v;
        cin >> x >> y >> v;
        e[x].emplace_back(y, v);
        e[y].emplace_back(x, v);
    }
    dfs(1, 0);
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