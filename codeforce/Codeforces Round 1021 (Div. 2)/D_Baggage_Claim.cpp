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
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti;
void work() {
    int n, m, k;
    cin >> n >> m >> k;
    vi xs(k + 1), ys(k + 1);
    rep(i, 0, k) { cin >> xs[i] >> ys[i]; }
    int ans = 1;
    rep(i, 0, k - 1) {
        int dx = abs(xs[i + 1] - xs[i]);
        int dy = abs(ys[i + 1] - ys[i]);
        int d = dx + dy;
        if (d < 2 || d > 2) {  
            ans = 0;
            break;
        }
        if (dx == 1 && dy == 1) {
            ans = ans * 2 % mod;
        }
    }
    print(ans);
}

    signed
    main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}