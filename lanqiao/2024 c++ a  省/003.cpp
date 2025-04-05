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
int p1[N], p2[N];
vector<int> e1[N], e2[N];
int ans = 0;
void dfs(int u1, int u2, int f1, int f2, int cnt) {
    for (int v1 : e1[u1])
        if (v1 != f1)
            for (int v2 : e2[u2])
                if (v2 != f2 && p1[v1] == p2[v2]) dfs(v1, v2, u1, u2, cnt + 1);
    ans = max(ans, cnt);
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> p1[i];
    rep(i, 1, m) cin >> p2[i];
    rep(i, 1, n - 1) {
        int x, y;
        cin >> x >> y;
        e1[x].push_back(y);
        e1[y].push_back(x);
    }
    rep(i, 1, m - 1) {
        int x, y;
        cin >> x >> y;
        e2[x].push_back(y);
        e2[y].push_back(x);
    }
    dfs(1, 1, 0, 0, 1);
    if (p1[1] != p2[1])
        print(0);
    else
        cout << ans << endl;
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