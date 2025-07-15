#include <bits/stdc++.h>
using namespace std;

int m, n, N;
vector<int> a;
int target, best = INT_MAX;
vector<bool> vis, inCand;

inline int idx(int r, int c) { return r * m + c; }
inline bool inside(int r, int c) { return r >= 0 && r < n && c >= 0 && c < m; }

void dfs(vector<int>& cand, int curSum, int curCnt) {
    if (curSum == target) {
        best = min(best, curCnt);
        return;
    }
    if (curSum > target || curCnt >= best) return;
    // try each candidate cell
    int sz = cand.size();
    for (int i = 0; i < sz; i++) {
        int id = cand[i];
        int v = a[id];
        if (curSum + v > target) continue;
        // pick this cell
        vis[id] = true;
        // build new candidate list
        vector<int> ncand;
        ncand.reserve(sz + 4);
        fill(inCand.begin(), inCand.end(), false);
        for (int j = 0; j < sz; j++) {
            if (j == i) continue;
            ncand.push_back(cand[j]);
            inCand[cand[j]] = true;
        }
        int r = id / m, c = id % m;
        // add new neighbors of id
        static int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (!inside(nr, nc)) continue;
            int nid = idx(nr, nc);
            if (!vis[nid] && !inCand[nid]) {
                ncand.push_back(nid);
                inCand[nid] = true;
            }
        }
        dfs(ncand, curSum + v, curCnt + 1);
        vis[id] = false;
        if (best == curCnt + 1) break;  // found optimal at this depth
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n;
    N = m * n;
    a.resize(N);
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % 2) {
        cout << 0;
        return 0;
    }
    target = sum / 2;
    vis.assign(N, false);
    inCand.assign(N, false);
    // start from (0,0)
    vis[0] = true;
    vector<int> cand;
    // initial neighbors of (0,0)
    int r0 = 0, c0 = 0;
    static int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    for (int d = 0; d < 4; d++) {
        int nr = r0 + dr[d], nc = c0 + dc[d];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
            int id = idx(nr, nc);
            cand.push_back(id);
            inCand[id] = true;
        }
    }
    dfs(cand, a[0], 1);
    if (best == INT_MAX) best = 0;
    cout << best;
    return 0;
}