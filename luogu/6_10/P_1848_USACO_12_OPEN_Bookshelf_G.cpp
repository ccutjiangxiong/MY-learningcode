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
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
vi e[N];
int l = 1, mid, r;
int q[N], stk[2][N], f[N], top[2], ff[N];
void push(int x, int mo) {
    if (!top[mo] || (ff[stk[mo][top[mo]]] > ff[x])) stk[mo][++top[mo]] = x;
}

void rebuild() {
    mid = (l + r) >> 1, top[0] = top[1] = 0;
    rem(i, mid, l) push(i, 0);
    rep(i, mid + 1, r) push(i, 1);
}
void work() {
    cin >> n >> m;
    int st = 1, sum = 0;
    rep(i, 1, n) cin >> a[i]>>b[i];

    rep(i, 1, n) {
        sum += b[i];
        while (sum > m) sum -= b[st++];
        while (l <= r and a[q[r]] <= a[i]) {
            rep(k, 0, 1) if (top[k] && stk[k][top[k]] == r)-- top[k];
            if (--r <= mid) rebuild();
        }
        ff[r + 1] = (l > r) ? f[st - 1] + a[i] : f[q[r]] + a[i];
        q[++r] = i, push(r, 1);
        rep(k, 0, 1) if (stk[k][top[k]] == l)-- top[k];
        while (l <= r && q[l] < st) {
            if (++l > mid) rebuild();
            rep(k, 0, 1) if (top[k] && stk[k][top[k]] == l)-- top[k];
        }
        f[i] = f[st - 1] + a[q[l]];
        rep(k, 0, 1) if (top[k]) f[i] = min(f[i], ff[stk[k][top[k]]]);
    }
    pt(f[n]);
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