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
int ti = 1, n, q, a[N];
int bi[N];
int lowbit(int x) { return x & -x; }
void update(int x, int v) {
    for (; x <= N - 1; x += lowbit(x)) bi[x] += v;
}
int query(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) res += bi[x];
    return res;
}

void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    cin >> q;
    rep(_, 1, q) {
        int x;
        cin >> x;
        rep(i, 1, 100) bi[i] = 0;
        vi pre(n + 1), suf(n + 2);
        rep(i, 1, n) pre[i] = pre[i - 1] + (a[i] > x);
        int ans = 0, mi = inf;
        rem(i, n, 1) {
            update(a[i], 1);
            int y = pre[i - 1] + query(111) - query(a[i]);
            mi = min(y, mi);
        }
        print(mi);
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