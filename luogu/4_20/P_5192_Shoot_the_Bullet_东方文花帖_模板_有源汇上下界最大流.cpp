#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
using pii = pair<int, int>;
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
const int N = 2e6 + 5, INF = 1e18;
vector<pii> e[N];
int g[N], d[N], cur[N], cnt = 0;
int lc[N], uc[N], y[N], f[N];

void add(int u, int v, int c, int id) {
    int x = cnt++, y = cnt++;
    e[u].emplace_back(v, x);
    e[v].emplace_back(u, y);
    g[x] = c, g[y] = 0;
    f[id] = x;
}

bool bfs(int s, int t) {
    memset(d, 0, sizeof d);
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : e[u]) {
            if (g[w] && !d[v]) {
                d[v] = d[u] + 1;
                q.push(v);
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
        if (g[w] && d[v] == d[u] + 1) {
            int f = dfs(v, min(flow, g[w]), t);
            g[w] -= f;
            g[w ^ 1] += f;
            sum += f;
            flow -= f;
            if (!flow) break;
        }
    }
    if (!sum) d[u] = 0;
    return sum;
}

int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        memset(cur, 0, sizeof cur);
        ans += dfs(s, INF, t);
    }
    return ans;
}

void solve() {
    int n, m;
    while (cin >> n >> m) {
        cnt = 0;
        rep(i, 0, n + m + 3) e[i].clear();
        memset(y, 0, sizeof y);

        // 少女至少G_x张
        vi G(m);
        rep(i, 0, m - 1) cin >> G[i];

        int s = 0, t = n + m + 1;
        int ss = n + m + 2, tt = n + m + 3;
        int totf = 0;

        // 天到少女的边
        rep(i, 1, n) {
            int C, D;
            cin >> C >> D;
            // 源点到天，容量D_i
            add(s, i, D, 0);
            rep(j, 1, C) {
                int T, L, R;
                cin >> T >> L >> R;
                T++;  // 转换为1-based
                // 天到少女，容量R-L，下界L
                add(i, n + T, R - L, 0);
                y[i] -= L;
                y[n + T] += L;
            }
        }

        // 少女到汇点，下界G_x
        rep(i, 1, m) {
            add(n + i, t, INF, 0);
            y[n + i] -= G[i - 1];
            y[t] += G[i - 1];
        }

        // 添加超级源汇
        add(t, s, INF, 0);  // 循环边
        rep(i, 0, n + m + 1) {
            if (y[i] > 0) {
                add(ss, i, y[i], 0);
                totf += y[i];
            } else if (y[i] < 0) {
                add(i, tt, -y[i], 0);
            }
        }

        // 判断可行流
        int flow = dinic(ss, tt);
        if (flow != totf) {
            cout << -1 << "\n\n";
            continue;
        }

        // 计算最大流
        flow = dinic(s, t);
        cout << flow << "\n\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}