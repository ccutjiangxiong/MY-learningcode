#include <bits/stdc++.h>
using namespace std;

// --------------- 最大二分匹配（Hopcroft-Karp）模板 ---------------
static const int INF = 0x3f3f3f3f;
struct HopcroftKarp {
    int n_left, n_right;
    vector<vector<int>> adj;
    vector<int> matchR, matchL, dist;

    HopcroftKarp(int nL, int nR) : n_left(nL), n_right(nR) {
        adj.assign(n_left, {});
        matchR.assign(n_right, -1);
        matchL.assign(n_left, -1);
        dist.assign(n_left, 0);
    }

    void addEdge(int l, int r) { adj[l].push_back(r); }

    bool bfs() {
        queue<int> q;
        for (int i = 0; i < n_left; i++) {
            if (matchL[i] == -1) {
                dist[i] = 0;
                q.push(i);
            } else
                dist[i] = INF;
        }
        int flag = INF;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] > flag) break;
            for (auto &v : adj[u]) {
                int w = matchR[v];
                if (w < 0) {
                    flag = dist[u] + 1;
                } else if (w >= 0 && dist[w] == INF) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return flag != INF;
    }

    bool dfs(int u) {
        if (u < 0) return true;
        for (auto v : adj[u]) {
            int w = matchR[v];
            if (w < 0 || (w >= 0 && dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int maximumMatch() {
        int res = 0;
        while (bfs()) {
            for (int i = 0; i < n_left; i++) {
                if (matchL[i] < 0 && dfs(i)) res++;
            }
        }
        return res;
    }
};

// --------------- 主逻辑部分 ---------------

// 判断 T 形合法的四个坐标
// 这里演示了 4 种方向，以 (x,y) 为中心
vector<vector<pair<int, int>>> T_shapes = {{{-1, 0}, {0, 0}, {1, 0}, {0, 1}},  // 题目给的示例方向
                                           {{-1, 0}, {0, 0}, {1, 0}, {0, -1}},
                                           {{0, -1}, {0, 0}, {0, 1}, {1, 0}},
                                           {{0, -1}, {0, 0}, {0, 1}, {-1, 0}}};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;  // 数据组数
    cin >> D;
    while (D--) {
        int n;
        cin >> n;
        vector<string> mat(n);
        for (int i = 0; i < n; i++) {
            cin >> mat[i];
        }

        // 收集所有为 '1' 的单元格，给它编号(右侧节点)
        // cellID[i][j] 用来映射到“右侧节点”的编号
        vector<vector<int>> cellID(n, vector<int>(n, -1));
        int rCount = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == '1') {
                    cellID[i][j] = rCount++;
                }
            }
        }

        // 收集所有可行的 T 形区域，给它编号(左侧节点)
        // 每个 T 形区域如果包含至少一个 '1' 才有意义，但这里先收集所有 T，可在建边时判断
        // tID[x][y][dir] 表示以 (x,y) 为中心第 dir 种形态 的左侧节点编号
        // 方便演示，这里直接把每个可行 T 形加入一个 vector，统一管理
        vector<int> centersX, centersY, centersDir;  // 记录所有可能的T形
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                for (int dir = 0; dir < 4; dir++) {
                    bool ok = true;
                    for (auto &p : T_shapes[dir]) {
                        int nx = x + p.first, ny = y + p.second;
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        centersX.push_back(x);
                        centersY.push_back(y);
                        centersDir.push_back(dir);
                    }
                }
            }
        }

        HopcroftKarp hk((int)centersX.size(), rCount);

        // 建立边：若该 T 形区域覆盖的4个坐标中存在一些 '1' 单元，则分别向这些单元连边
        for (int i = 0; i < (int)centersX.size(); i++) {
            int x = centersX[i], y = centersY[i], d = centersDir[i];
            bool hasOne = false;  // 判断是否至少包含一个 '1'
            vector<int> covered;
            for (auto &p : T_shapes[d]) {
                int nx = x + p.first, ny = y + p.second;
                if (mat[nx][ny] == '1') {
                    covered.push_back(cellID[nx][ny]);
                    hasOne = true;
                }
            }
            // 只有在包含至少一个 '1' 的情况下，这个 T 形才有意义
            if (!hasOne) continue;
            for (int c : covered) {
                hk.addEdge(i, c);
            }
        }

        // 求最大匹配，对应最多能“选”多少个 T 形区域
        cout << hk.maximumMatch() << "\n";
    }
    return 0;
}