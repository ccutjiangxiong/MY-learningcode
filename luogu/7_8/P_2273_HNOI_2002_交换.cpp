
#include <bits/stdc++.h>
    using namespace std;
using ll = long long;

const int MAXN = 10000 + 5;
int n, m;
vector<pair<int, int>> edges;
vector<int> g[MAXN];
int tin[MAXN], low[MAXN], timer;
bool is_bridge[200000 + 5];

void dfs_br(int u, int pe) {
    tin[u] = low[u] = ++timer;
    for (int ei : g[u]) {
        auto [v, id] = edges[ei];
        if (id == pe) continue;
        if (!tin[v]) {
            dfs_br(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) is_bridge[id] = true;
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

int comp[MAXN], comp_cnt;
vector<int> tree_deg;

void dfs_comp(int u, int c) {
    comp[u] = c;
    for (int ei : g[u]) {
        auto [v, id] = edges[ei];
        if (comp[v] == 0 && !is_bridge[id]) dfs_comp(v, c);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    // read 2*m integers separated by commas
    string line;
    if (m > 0) {
        cin >> line;
        vector<int> a;
        int num = 0;
        bool innum = false;
        for (char ch : line) {
            if (isdigit(ch)) {
                innum = true;
                num = num * 10 + (ch - '0');
            } else {
                if (innum) {
                    a.push_back(num);
                    num = 0;
                    innum = false;
                }
            }
        }
        if (innum) a.push_back(num);
        for (int i = 0; i < m; i++) {
            int u = a[2 * i], v = a[2 * i + 1];
            edges.emplace_back(v, u);  // we'll store (to,from)
            edges.emplace_back(u, v);
            int id = i;
            g[u].push_back(2 * i);
            g[v].push_back(2 * i + 1);
        }
    }
    // 1. find bridges
    for (int i = 1; i <= n; i++)
        if (!tin[i]) dfs_br(i, -1);
    // 2. build 2-edge-cc
    for (int i = 1; i <= n; i++) {
        if (comp[i] == 0) {
            ++comp_cnt;
            dfs_comp(i, comp_cnt);
        }
    }
    tree_deg.assign(comp_cnt + 1, 0);
    // 3. build bridge-tree degrees
    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) {
            auto [v, u] = edges[2 * i];
            int c1 = comp[u], c2 = comp[v];
            tree_deg[c1]++;
            tree_deg[c2]++;
        }
    }
    // 4. sum leaves L_i
    int sumL = 0;
    for (int i = 1; i <= comp_cnt; i++) {
        if (tree_deg[i] == 0)
            sumL += 2;
        else if (tree_deg[i] == 1)
            sumL += 1;
    }
    // 5. answer
    int ans = (sumL + 1) / 2;
    cout << ans << "\n";
    return 0;
}