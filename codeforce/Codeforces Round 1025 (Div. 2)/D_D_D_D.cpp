#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, l;
        cin >> n >> m >> l;
        vector<int> A(l);
        ll sumA = 0;
        int ac = INT_MAX;
        for (int i = 0; i < l; i++) {
            cin >> A[i];
            sumA += A[i];
            if (A[i] & 1) ac = min(ac, A[i]);
        }
        if (ac == INT_MAX) ac = -1;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> dist(n + 1, -1), color(n + 1, -1);
        queue<int> q;
        dist[1] = 0;
        color[1] = 0;
        q.push(1);
        bool is_bip = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else {
                    if (color[v] == color[u]) {
                        is_bip = false;
                    }
                }
            }
        }

        string tmp(n, '0');
        for (int i = 1; i <= n; i++) {
            ll d = dist[i];
            if (d < 0 || d > sumA) {
                tmp[i - 1] = '0';
            } else if (!is_bip) {
                tmp[i - 1] = '1';
            } else {
                int need = d & 1;
                if ((sumA & 1) == need) {
                    tmp[i - 1] = '1';
                } else if (ac != -1 && sumA - ac >= d) {
                    tmp[i - 1] = '1';
                } else {
                    tmp[i - 1] = '0';
                }
            }
        }

        cout << tmp << "\n";
    }

    return 0;
}