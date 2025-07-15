#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define pb emplace_back
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 2e6 + 6, inf = 1e18, mod = 1e9 + 7;
int ti;
int a[N];
int n;
vi e[N];
int q;
int tr[N][10];
int cnt = 1;
int g[N][55];
// void insert(int x) {
//     int p = 0;
//     rep(i, 0, 31) {
//         int y = (x >> i) & 1;
//         if (tr[p][y] == 0) tr[p][y] = ++cnt;
//         p = tr[p][y];
//     }
//     tr[p][3]++;
// }
void dfs(int x, int p, int k) {
    // int y = (x >> k) & 1;
    int y = x & (1ll << (31 - k));
    if (k == 31) {
        tr[p][3]++;
        tr[p][4] += y;
        return;
    }
    if (tr[p][y] == 0) tr[p][y] = ++cnt;
    int t = tr[p][y];
    dfs(x, t, k + 1);
    
}
int ask(int x) {
    int p = 1;
    int res = 0;
    rep(i, 0, 31) {
        int y = (x >> i) & 1;
        if (y == 1) {
            int t = tr[p][0];
            int su = tr[t][4];
            res += (su ^ x) - su;
        }
        if (tr[p][y] == 0) break;
        p = tr[p][y];
    }
    return res;
}
void work() {
    cin >> n >> q;
    int su = 0;
    rep(i, 1, n) cin >> a[i], dfs(a[i], 1, 0), su += a[i];
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        // e[u].pb(v);
        // e[v].pb(u);
    }
    rep(i, 1, q) {
        int x;
        cin >> x;
        cout << ask(x) + tr[1][4] << ' ' << ask(x) << endl;
    }
    rep(i, 1, n) rep(j, 0, 5) tr[i][j] = 0;
    cnt = 1;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}