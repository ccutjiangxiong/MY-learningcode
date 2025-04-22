#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

void be(int u,int v,int w,auto edges[N]) {
    edges[u].pb({v,w}), edges[v].pb({u,w});
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
vector<pii> e[N];
int vis[N], dis[N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
void dij(int s,int n) {
  memset(dis, 0x3f, sizeof(int)*(n+1));
  dis[s] = 0;
  pq.push({0, s});
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u])
      continue;
    vis[u] = 1;
    for (auto [v, w] : e[u]) {
      if (dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        pq.emplace(dis[v], v);
      }
    }
  }
}
int ti=1;
int r, c, d;
int gr[2222][222],pre[2222][222];
void work() {
    cin >> r >> c;
    int ans = 0;  // Declare and initialize ans

    // Read the grid and calculate prefix sums
    rep(i, 1, r) rep(j, 1, c) {
        cin >> gr[i][j];
        pre[i][j] = pre[i][j - 1] + gr[i][j];
    }

    // Build the graph
    rep(i, 1, r) {
        if (i > 1) {
            e[i].emplace_back(i - 1, gr[i][1]);          // Connect to the row above
            e[i + r].emplace_back(i - 1 + r, gr[i][c]);  // Connect to the row above (right side)
        }
        if (i < r) {
            e[i].emplace_back(i + 1, gr[i][1]);          // Connect to the row below
            e[i + r].emplace_back(i + 1 + r, gr[i][c]);  // Connect to the row below (right side)
        }
        e[i].emplace_back(i + r, pre[i][c - 1]);  // Connect left to right within the row
        e[i + r].emplace_back(i, pre[i][c - 1]);  // Connect right to left within the row
    }

    // Multi-source shortest path
    rep(i, 1, r * 2) dij(i, r * 2);

    // Process queries
    int tx = 1, ty = 1;
    cin >> d;
    while (d--) {
        int x, y;
        cin >> x >> y;

        // Calculate the minimum cost for the query
        int res0 = (tx == x)
                       ? (ty < y ? pre[x][y - 1] - pre[x][ty - 1] : pre[x][ty - 1] - pre[x][y - 1])
                       : inf;
        int res1 = pre[tx][ty - 1] + dis[x] + pre[x][y - 1];
        int res2 = pre[tx][ty - 1] + dis[x] + pre[x][y - 1];
        int res3 = pre[tx][ty - 1] + dis[x + r] + pre[x][y - 1];
        int res4 = pre[tx][ty - 1] + dis[x + r] + pre[x][y - 1];

        ans += min({res0, res1, res2, res3, res4});
        tx = x, ty = y;
    }

    cout << ans + gr[tx][ty] << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}