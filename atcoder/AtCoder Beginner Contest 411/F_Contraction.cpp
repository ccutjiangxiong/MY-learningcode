#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges(M + 1);
    for (int i = 1; i <= M; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int Q;
    cin >> Q;
    vector<int> ops(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> ops[i];
    }

    // 初始化图节点并查集
    vector<int> fa(N + 1);
    iota(fa.begin(), fa.end(), 0);

    function<int(int)> find = [&](int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); };

    // 每个代表点维护邻接点集合
    vector<unordered_map<int, int>> adj(N + 1);
    set<pair<int, int>> edgeSet;  // 简单图（无重边）

    for (int i = 1; i <= M; ++i) {
        int u = edges[i].first, v = edges[i].second;
        adj[u][v]++;
        adj[v][u]++;
        edgeSet.insert({min(u, v), max(u, v)});
    }

    // 棋子位置：piece[i] = 当前 i 号棋子在哪个图顶点
    vector<int> piece(N + 1);
    iota(piece.begin(), piece.end(), 0);  // 初始 i 号棋子在 i 点

    for (int x : ops) {
        auto [u, v] = edges[x];
        int a = find(piece[u]), b = find(piece[v]);
        if (a == b || !adj[a].count(b)) {
            cout << edgeSet.size() << '\n';
            continue;
        }

        // 合并 b -> a（启发式略）
        if (adj[a].size() < adj[b].size()) swap(a, b);

        // 删除连接 a-b 的边数
        edgeSet.erase({min(a, b), max(a, b)});
        adj[a][b]--;
        if (adj[a][b] == 0) adj[a].erase(b);
        adj[b][a]--;
        if (adj[b][a] == 0) adj[b].erase(a);

        // 合并邻接点
        for (auto &[to, cnt] : adj[b]) {
            adj[a][to] += cnt;
            adj[to][a] += cnt;
            adj[to].erase(b);
            if (a != to) edgeSet.insert({min(a, to), max(a, to)});
        }
        adj[b].clear();

        fa[b] = a;

        // 更新棋子位置：所有在 b 的棋子 -> a
        for (int i = 1; i <= N; ++i) {
            if (find(piece[i]) == b) {
                piece[i] = a;
            }
        }

        cout << edgeSet.size() << '\n';
    }

    return 0;
}
