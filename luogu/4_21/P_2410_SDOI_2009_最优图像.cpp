#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define vii vector<pii>
#define viii vector<piii>
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti = 1;
vector<tuple<int, int, float>> e[N];
int g[N], cur[N], f[N], vis[N];
float d[N], dis[N];
int n, m, s, t, cnt = 0;
void add(int u, int v, int c, float w, int id) {
    int x = cnt++, y = cnt++;
    e[u].pb(v, x, w);
    e[v].pb(u, y, 1.0 / w);
    g[x] = c, g[y] = 0, f[id] = x;
}
bool bfs(int s, int t) {
    rep(i, 0, t) d[i] = -1;
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w, ww] : e[u]) {
            if (g[w] && d[v] == -1) {
                d[v] = d[u] * ww;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}
int dfs(int u, int flow, int t) {
    if (u == t) return flow;
    int sum = 0;
    for (int &i = cur[u]; i < e[u].size(); i++) {
        auto [v, w, ww] = e[u][i];
        if (d[v] == d[u] * ww && g[w]) {
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
        rep(i, 0, t) cur[i] = 0;
    }
    return ans;
}
int p[222][222], a[N], b[N];

int fid[105][105];

void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> p[i][j];
    rep(i, 1, n) cin >> a[i];
    rep(j, 1, m) cin >> b[j];

    s = 0;
    t = n + m + 1;
    cnt = 0;
    // clear graph
    rep(i, 0, t) { e[i].clear(); }
    rep(i, 1, n) rep(j, 1, m) {
        fid[i][j] = cnt;  // this is the index of the forward edge
        add(i, n + j, 1, p[i][j] * 0.01, 0);
    }
    rep(i, 1, n) add(s, i, a[i], 0, 0);
    rep(j, 1, m) add(n + j, t, b[j], 0, 0);
    dinic(s, t);
    vector<string> ans(n, string(m, '0'));
    rep(i, 1, n) rep(j, 1, m) if (g[fid[i][j]] == 0) ans[i - 1][j - 1] = '1';
    for (auto &row : ans) cout << row << "\n";
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