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
using ull = uint64_t;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, a[N];
vector<pii> e[N];
int dis[N], cnt[N], vis[N];
bool spfa(int s) {
    me(dis, 0xcf);  // 初始化为负无穷
    me(vis, 0);
    me(cnt, 0);
    queue<int> q;
    dis[s] = 0, vis[s] = 1, q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : e[u]) {
            if (dis[v] < dis[u] + w) {  // 改为求最长路
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) return false;  // 存在正环，无解
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return true;
}
void work() {
    cin >> n >> m;
    rep(i, 1, m) {
        int l, r, s;
        cin >> l >> r >> s;
        e[l - 1].pb(r, s);
        e[r].pb(l - 1, -s);
    }
    // rep(i, 1, n) e[0].pb(i, 0);
    rep(i, 1, n) e[i - 1].pb(i, 1);
    if (spfa(0)) {
        print(dis[n]);
    } else
        print(-1);
    // print(dis[1]);
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