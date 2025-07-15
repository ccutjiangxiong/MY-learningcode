#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];
int gr[555][555], vis[555][555];
int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
priority_queue<piii, vector<piii>, greater<>> pq;
// int
void work() {
    cin >> n >> m >> k;
    cin >> x >> y;
    rep(i, 1, n) rep(j, 1, m) cin >> gr[i][j];
    pq.ep(gr[x][y], x, y);
    while (pq.size()) {
        auto [u, x, y] = pq.top();

        pq.pop();
        if (vis[x][y]++) continue;

        if (ans > (ill)u * k || ans == 0)
            ans += u;
        else
            continue;

        rep(i, 0, 3) {
            int nx = x + d[i][0], ny = y + d[i][1];

            if (nx && ny && nx <= n && ny <= m && !vis[nx][ny]) pq.ep(gr[nx][ny], nx, ny);
        }
    }
    print(ans);
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