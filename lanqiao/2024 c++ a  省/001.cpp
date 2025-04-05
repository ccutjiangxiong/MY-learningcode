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
int ans = 0;
int mat[11][11];
int dfs(int x, int y, int a, int b) {
    if (x == 6) y++, x = 1;
    int ans = 0;
    rep(i, 1, 5) if (mat[i][1] && mat[i][1] == mat[i][2] && mat[i][2] == mat[i][3] &&
                     mat[i][3] == mat[i][4] && mat[i][4] == mat[i][5]) return 0;

    rep(i, 1, 5) if (mat[1][i] && mat[1][i] == mat[2][i] && mat[2][i] == mat[3][i] &&
                     mat[3][i] == mat[4][i] && mat[4][i] == mat[5][i]) return 0;
    if (mat[1][1] && mat[1][1] == mat[2][2] && mat[2][2] == mat[3][3] && mat[3][3] == mat[4][4] &&
        mat[4][4] == mat[5][5])
        return 0;
    if (mat[1][5] && mat[1][5] == mat[2][4] && mat[2][4] == mat[3][3] && mat[3][3] == mat[4][2] &&
        mat[4][2] == mat[5][1])
        return 0;
    if (a == 0 && b == 0) return 1;
    if (a) {
        mat[x][y] = 1;
        ans += dfs(x + 1, y, a - 1, b);
        mat[x][y] = 0;
    }
    if (b) {
        mat[x][y] = 2;
        ans += dfs(x + 1, y, a, b - 1);
        mat[x][y] = 0;
    }
    return ans;
}
void work() { cout << dfs(1, 1, 12, 13); }
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}