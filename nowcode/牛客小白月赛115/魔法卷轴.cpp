#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n, -1), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};
// … #include/前面不变 …
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<long long> ts;
        ts.reserve(2 * n);
        for (auto v : a) {
            ts.push_back(v + 1);
            if (v > 1) ts.push_back(v - 1);
        }
        sort(ts.begin(), ts.end());
        ts.erase(unique(ts.begin(), ts.end()), ts.end());
        auto getid = [&](long long x) {
            return int(lower_bound(ts.begin(), ts.end(), x) - ts.begin());
        };
        int M = ts.size();

        // 收集“单选”和“双选”任务
        vector<int> singleCnt(M, 0);
        vector<pair<int, int>> edges;
        for (auto v : a) {
            int idr = getid(v + 1);
            if (v > 1) {
                int idl = getid(v - 1);
                edges.emplace_back(min(idl, idr), max(idl, idr));
            } else {
                singleCnt[idr]++;
            }
        }

        // 前缀单选计数
        vector<int> prefSingle(M);
        for (int i = 0; i < M; i++) {
            prefSingle[i] = singleCnt[i] + (i > 0 ? prefSingle[i - 1] : 0);
        }
        // 前缀“必须在≤i范围内分配”的双选任务数
        vector<int> prefEdge(M);
        for (auto &e : edges) {
            // 只有当时刻ID ≤ mx 才算“锁定”到前缀
            prefEdge[e.second]++;
        }
        for (int i = 1; i < M; i++) {
            prefEdge[i] += prefEdge[i - 1];
        }

        bool ok = true;
        for (int i = 0; i < M; i++) {
            // i+1 是时刻点数量
            if (prefSingle[i] + prefEdge[i] > i + 1) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}