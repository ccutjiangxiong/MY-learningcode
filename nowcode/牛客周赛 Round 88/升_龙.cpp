#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill=__int128;
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n, k;
int a[N], f[N];
vector<int> e[N];
int p1[N], p2[N];
priority_queue<pii> pq;
int dfs(int u, int fa) {
    p1[u] = p1[fa] + a[u];
    for (int v : e[u])
        if (v != fa)
            p2[u] = max(dfs(v, u), p2[u]);
        else if (vector<int>{fa} == e[u])
            pq.emplace(p1[u], u);
    return p2[u] += a[u];
}
bool judge(int u, int fa) {
    while (u != 1) {
        if (u == fa) return false;
        u = f[u];
    }
    return true;
}
void work() {
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i];
    rep(i, 2, n) {
        int u;
        cin >> u;
        f[i] = u;
        e[u].push_back(i);
        e[i].push_back(u);
    }
    dfs(1, 0);
    rep(i, 1, k) {
        int x, y;
        cin >> x >> y;
        int ans = max(p1[f[x]], p2[x] + p1[y]);
        vector<pii> h;
        while (pq.size() && pq.top().first > ans) {
            pii q = pq.top();
            pq.pop();
            h.push_back(q);
            if (judge(q.second, x)) {
                ans = q.first;
                break;
            }
        }
        cout << ans << endl;
        for (auto q : h) pq.emplace(q);
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