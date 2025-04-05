#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n, m;
int mat[11][11], vis[11][11];
int d[11][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
vector<int> ans;
bool dfs(int x, int y, int k) {
    vis[x][y] = ans.size() + 1;
    if (x == n && y == n && (int)ans.size() == n * n - 1) {
        for (int x : ans) cout << x;
        return true;
    }

    rep(i, 0, 7) {
        int nx = x - d[i][1], ny = d[i][0] + y;
        if (nx < 1 || ny < 1 || nx > n || ny > n) continue;
        if (d[i][0] && d[i][1] && (abs(vis[x][ny] - vis[nx][y]) == 1) && vis[x][ny] && vis[nx][y])
            continue;
        if (mat[nx][ny] == ((k + 1) % m) && !vis[nx][ny]) {
            ans.push_back(i);
            if (dfs(nx, ny, (k + 1) % m)) return true;
            ans.pop_back();
        }
    }
    vis[x][y] = 0;
    return false;
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, n) cin >> mat[i][j];
    if (mat[1][1] != 0 || !dfs(1, 1, 0)) print(-1);
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