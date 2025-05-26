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

int ti = 1;
void work() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = 1;
    rep(i, 1, k) n *= 3;

    // build leaf array
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = s[i] - '0';

    // dfs returns {value, weight}
    function<pair<int, int>(int, int)> dfs = [&](int l, int r) -> pair<int, int> {
        if (l == r) {
            // leaf: its own bit, weight = 1
            return {a[l], 1};
        }
        int len = (r - l + 1) / 3;
        auto x = dfs(l, l + len - 1);
        auto y = dfs(l + len, l + 2 * len - 1);
        auto z = dfs(l + 2 * len, r);

        int cnt0 = (x.first == 0) + (y.first == 0) + (z.first == 0);
        int cnt1 = 3 - cnt0;

        // all three same
        if (cnt0 == 3) {
            array<int, 3> b = {x.second, y.second, z.second};
            sort(b.begin(), b.end());
            return {0, b[0] + b[1]};
        }
        if (cnt1 == 3) {
            array<int, 3> b = {x.second, y.second, z.second};
            sort(b.begin(), b.end());
            return {1, b[0] + b[1]};
        }
        // exactly two zeros
        if (cnt0 == 2) {
            int best = LLONG_MAX;
            if (x.first == 0) best = min(best, x.second);
            if (y.first == 0) best = min(best, y.second);
            if (z.first == 0) best = min(best, z.second);
            return {0, best};
        }
        // exactly two ones
        int best = LLONG_MAX;
        if (x.first == 1) best = min(best, x.second);
        if (y.first == 1) best = min(best, y.second);
        if (z.first == 1) best = min(best, z.second);
        return {1, best};
    };

    auto ans = dfs(0, n - 1);
    print(ans.second);
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