#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 1e4 + 5;
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
int n, m;
int k[N], ask[N];
vector<int> q1, q2;
int vis[N];
int ink[N];
bool vin[555][1111][1111];
vector<int> ans[N], ans2[N];
void dfs(int x, int u, int v) {
    if (vin[x][u][v]) return;
    vin[x][u][v] = 1;
    if (!vis[u * v] && ink[u * v]) {
        for (int y : q1) ans[u * v].push_back(y), vis[u * v] = 1;
        for (int y : q2) ans2[u * v].push_back(y), vis[u * v] = 1;
        vis[u * v] = 1;
    }
    if (x > n) return;
    if (u * (v + k[x]) <= 1000 && v + k[x] <= 1000) {
        q1.push_back(k[x]);
        dfs(x + 1, u, v + k[x]);
        q1.pop_back();
    }
    if (v * ((u + k[x])) <= 1000 && u + k[x] <= 1000) {
        q2.push_back(k[x]);
        dfs(x + 1, u + k[x], v);
        q2.pop_back();
    }
    dfs(x + 1, u, v);
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> k[i];
    rep(i, 1, m) cin >> ask[i];
    rep(i, 1, m) ink[ask[i]] = 1;
    sort(k + 1, k + 1 + n);
    dfs(1, 0, 0);
    rep(i, 1, m) {
        if (vis[ask[i]]) {
            print("Yes");
            print(ans[ask[i]].size(), ans2[ask[i]].size());
            for (int x : ans[ask[i]]) cout << x << ' ';
            cout << endl;
            for (int x : ans2[ask[i]]) cout << x << ' ';
            cout << endl;
        } else
            cout << "No" << endl;
    }
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