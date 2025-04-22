#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define ep emplace
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}
void be3(auto edges[N]) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[u].pb(v, w);
}
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int n;
vector<pii> e[N];
int dis[N], cnt[N], vis[N];
bool spfa(int s) {
    me(dis, 0x3f);
    queue<int> q;
    dis[s] = 0, vis[s] = 1, q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : e[u])
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
    }
    return false;
}
int ti = 1;
void work() {
    int m, s;
    cin >> n >> m >> s;
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].pb(v, w);
    }
    spfa(s);
    rep(i, 1, n) cout << min(dis[i], 2147483647ll) << ' ';
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