#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
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
int n;
char mat[5555][5555];
int vis[22][22][22][22][4];
queue<tuple<piii, piii, int>> st;
int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int bfs() {
    st.push({{1, 1, 0}, {1, 1, 1}, 0});
    while (st.size()) {
        auto [p1, p2, t] = st.front();
        st.pop();
        auto [x1, y1, r1] = p1;
        auto [x2, y2, r2] = p2;
        if (vis[x1][y1][x2][y2][r1]++) continue;
        if (min({x1, x2, y1, y2}) == n) return t;
        int x3 = clamp(x1 + d[r1][0], 1LL, n);
        int y3 = clamp(y1 + d[r1][1], 1LL, n);
        int x4 = clamp(x2 + d[r2][0], 1LL, n);
        int y4 = clamp(y2 + d[r2][1], 1LL, n);
        if (mat[x3][y3] == 'H') x3 = x1, y3 = y1;
        if (mat[x4][y4] == 'H') x4 = x2, y4 = y2;
        if (x1 == n && y1 == n) x3 = y3 = n;
        if (x2 == n && y2 == n) x4 = y4 = n;
        st.emplace(make_tuple(x3, y3, r1), make_tuple(x4, y4, r2), t + 1);  // 移动
        st.emplace(make_tuple(x1, y1, (r1 + 3) % 4), make_tuple(x2, y2, (r2 + 3) % 4), t + 1);
        st.emplace(make_tuple(x1, y1, (r1 + 1) % 4), make_tuple(x2, y2, (r2 + 1) % 4),
                   t + 1);  // 右转
    }
    return -1;
}
void work() {
    cin >> n;
    rem(i, n, 1) rep(j, 1, n) cin >> mat[i][j];
    cout << bfs() << endl;
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