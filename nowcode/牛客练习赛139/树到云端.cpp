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

int ti=1;

// ...existing code...
void work() {
    int n;
    cin >> n;
    vector<vi> g(n + 1);
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<long long> t(n + 1);
    rep(i, 1, n) cin >> t[i];

    // build a rooted tree at 1
    vector<int> parent(n + 1), order;
    order.reserve(n);
    parent[1] = 0;
    order.pb(1);
    for (int i = 0; i < sz(order); i++) {
        int u = order[i];
        for (int v : g[u])
            if (v != parent[u]) {
                parent[v] = u;
                order.pb(v);
            }
    }

    // D[u] = t[u] - t[parent[u]]
    vector<long long> D(n + 1);
    for (int idx = 1; idx < sz(order); idx++) {
        int u = order[idx];
        D[u] = t[u] - t[parent[u]];
    }

    // children count and sum of D over children
    vector<int> cntCh(n + 1);
    vector<long long> sumD(n + 1);
    for (int u = 2; u <= n; u++) {
        cntCh[parent[u]]++;
        sumD[parent[u]] += D[u];
    }

    // constraints for S = sum of all val
    long long S_low = LLONG_MIN / 4, S_high = LLONG_MAX / 4;
    int parity = -1;
    for (int u = 1; u <= n; u++) {
        // a[u]*S + b[u] must be >= 2 and even
        long long a = (u == 1 ? 2LL - cntCh[u] : 1LL - cntCh[u]);
        long long b = (u == 1 ? sumD[u] : D[u] + sumD[u]);
        // ...existing code...
        for (int u = 1; u <= n; u++) {
             a = (u == 1 ? 2LL - cntCh[u] : 1LL - cntCh[u]);
            // 非根节点 b 应为 sumD - D，而不是 sumD + D
            b = (u == 1 ? sumD[u] : sumD[u] - D[u]);
            // ...后面不变...
        }
        // parity constraint when a is odd
        if (a & 1) {
            int p = (b % 2 + 2) % 2;
            if (parity < 0) parity = p;
        }

        if (a > 0) {
            // a*S + b >= 2  =>  S >= ceil((2 - b)/a)
            long long need = (2 - b + a - 1) / a;
            S_low = max(S_low, need);
        } else if (a < 0) {
            // a*S + b >= 2  =>  S <= floor((b - 2)/(-a))
            long long need = (b - 2) / (-a);
            S_high = min(S_high, need);
        } else {
            // a==0 => require b >= 2
            // (if b<2, no solution, but problem guarantees valid)
        }
    }

    // apply parity
    if (parity >= 0) {
        if (((S_low % 2 + 2) % 2) != parity) S_low++;
        if (((S_high % 2 + 2) % 2) != parity) S_high--;
    }

    long long S = S_low;  // unique valid sum

    // recover subtree sums sub[u]
    vector<long long> sub(n + 1);
    sub[1] = S;
    for (int idx = 1; idx < sz(order); idx++) {
        int u = order[idx];
        sub[u] = (S - D[u]) / 2;
    }

    // now recover each val[u] = sub[u] - sum(sub[child])
    vector<long long> val(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        long long s = 0;
        for (int v : g[u])
            if (parent[v] == u) s += sub[v];
        val[u] = sub[u] - s;
    }

    // output
    rep(i, 1, n) { cout << val[i] << (i == n ? '\n' : ' '); }
}
// ...existing code...
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}