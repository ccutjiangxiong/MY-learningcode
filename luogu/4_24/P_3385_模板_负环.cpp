#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fr first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;

void be(auto edges[N]) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[u].pb(v, w);
    if (w >= 0) edges[v].pb(u, w);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
vector<pii> e[N];
int n, m;
int dis[N], cnt[N], vis[N];
bool spfa(int s) {
    me(dis, 0x3f), me(vis, 0), me(cnt, 0);
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
int ti;
void work() {
    cin >> n >> m;
    for (auto &x : e) x.clear();
    rep(i, 1, m) be(e);
    print(spfa(1) ? "YES" : "NO");
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