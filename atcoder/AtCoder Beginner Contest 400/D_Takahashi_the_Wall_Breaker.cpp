#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i = 0; i < H; i++) {
        cin >> grid[i];
    }
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    A--;
    B--;
    C--;
    D--;

    vector<vector<int>> dist(H, vector<int>(W, INF));
    deque<pair<int, int>> dq;
    dist[A][B] = 0;
    dq.push_back({A, B});

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!dq.empty()) {
        auto [r, c] = dq.front();
        dq.pop_front();

        if (r == C && c == D) {
            cout << dist[r][c] << "\n";
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
            if (grid[nr][nc] == '#') continue;
            if (dist[nr][nc] > dist[r][c]) {
                dist[nr][nc] = dist[r][c];
                dq.push_front({nr, nc});
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int step = 1; step <= 2; step++) {
                int nr = r + dr[i] * step, nc = c + dc[i] * step;
                if (nr < 0 || nr >= H || nc < 0 || nc >= W) break;
                if (dist[nr][nc] <= dist[r][c] + 1) continue;
                dist[nr][nc] = dist[r][c] + 1;
                dq.push_back({nr, nc});
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}