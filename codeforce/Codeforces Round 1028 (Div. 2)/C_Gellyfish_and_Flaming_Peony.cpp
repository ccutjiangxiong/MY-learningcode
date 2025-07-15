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

int ti, n, m, k, a[5005], b[5005], x;
vi e[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int g = a[1];
    rep(i, 1, n) g = __gcd(g, a[i]);
    int cntg = 0;
    rep(i, 1, n) if (a[i] == g) cntg++;
    if (cntg) {
        print(n - cntg);
        return;
    }
    vi xx;
    xx.reserve(n);
    rep(i, 1, n) xx.pb(a[i]);
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    static int dist[5005];
    fill(dist, dist + 5001, -1);
    queue<int> q;
    for (int v : xx) {
        dist[v] = 0;
        q.push(v);
    }

    int best = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : xx) {
            int d = __gcd(u, v);
            if (dist[d] == -1) {
                dist[d] = dist[u] + 1;
                if (d == g) {
                    best = dist[d];
                    break;
                }
                q.push(d);
            }
        }
        if (best != -1) break;
    }
    print(best + (n - 1));
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