#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define ep emplace
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
vector<pii> e[N];
int g[N], d[N], cur[N], f[N];
int n, m, s, t, cnt = 0;
void add(int u, int v, int c, int id) {
    int x = cnt++, y = cnt++;
    e[u].emplace_back(v, x);
    e[v].emplace_back(u, y);
    g[x] = c, g[y] = 0, f[id] = x;
}
bool bfs(int s, int t) {
    rep(i, 0, N - 1) d[i] = inf;
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : e[u]) {
            if (g[w] && d[v] == inf) {
                q.push(v);
                d[v] = d[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}
int dfs(int u, int flow, int t) {
    if (u == t) return flow;
    int sum = 0;
    for (int &i = cur[u]; i < e[u].size(); i++) {
        auto [v, w] = e[u][i];
        if (d[v] == d[u] + 1 && g[w]) {
            int f = min(flow, g[w]);
            int re = dfs(v, f, t);
            g[w] -= re, g[w ^ 1] += re;
            sum += re, flow -= re;
            if (flow == 0) break;
        }
    }
    if (sum == 0) d[u] = 0;
    return sum;
}
int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        ans += dfs(s, inf, t);
        rep(i, 0, n + 2) cur[i] = 0;
    }
    return ans;
}
int ti = 1;
int x,y
int n1, n2, n3;
void work() {
    cin >> n1 >> n2 >> n3;
    cin >> m;
    int s = 0, t = n1 + n2 + n3 + 1 + n1;
    n = 2 * n1 + n2 + n3;
    rep(i, 1, m) {
        cin >> x >> y;
        add(y + 2 * n1, x, 1, 0);
        add(s, y + 2 * n1, 1, 0);
    }
    rep(i, 1, n1) add(i, i + n1, 1, 0);
    cin >> m;
    rep(i, 1, m) {
        cin >> x >> y;
        add(x + n1, y + 2 * n1 + n2, 1, 0);
        add(y + 2 * n1 + n2, t, 1, 0);
    }
    print(dinic(s, t));
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