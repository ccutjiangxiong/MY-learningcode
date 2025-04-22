#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
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

int ti = 1;
vector<pii> e[N];
int g[N], f[N], d[N], cur[N], cnt = 0;
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
            if (g[w] && d[v] == 0) {
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
        if (d[v] == d[u] + 1 && g[w] > 0) {
            int f = min(flow, g[w]);
            int re = dfs(v, f, t);
            g[w] -= re;
            g[w ^ 1] += re;
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
        memset(cur, 0, sizeof cur);
    }
    return ans;
}
int n, m, s, t;
int lc[N], uc[N], y[N];
void work() {
    cin >> n >> m >> s >> t;
    int totf = 0;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v >> lc[i] >> uc[i];
        add(u, v, uc[i] - lc[i], i);
        y[u] -= lc[i], y[v] += lc[i];
    }
    int ss = 0, tt = n + 1;
    add(t, s, inf, 0);
    rep(i, 1, n) {
        if (y[i] > 0)
            add(ss, i, y[i], 2*m), totf += y[i];
        else if (y[i] < 0)
            add(i, tt, -y[i], m + 1);
    }
    int ans = dinic(ss, tt);
    if (ans != totf)
        print("please go home to sleep");
    else {
        int id = f[0];
        int a = g[id ^ 1];
        g[f[0]] = g[f[0] ^ 1] = 0;
        cout << a - dinic(t, s) << "\n";
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