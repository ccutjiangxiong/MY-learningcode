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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    rep(i, 1, n) cin >> a[i];
    int total = accumulate(a.begin() + 1, a.end(), 0LL);
    vector<vector<int>> lvl(n + 1);
    int nid = 1;
    rep(i, 1, n) {
        rep(j, 1, a[i]) { lvl[i].push_back(nid++); }
    }

    vector<int> L(total + 1, -1), R(total + 1, -1);
    rep(i, 2, n) {
        auto &par = lvl[i - 1];
        auto &ch = lvl[i];
        vector<int> cnt(par.size(), 0);
        int pi = 0;
        for (int c : ch) {
            while (cnt[pi] == 2) pi++;
            int p = par[pi];
            if (cnt[pi] == 0)
                L[p] = c;
            else
                R[p] = c;
            cnt[pi]++;
        }
    }
    cout << lvl[1][0] << "\n";
    rep(i, 1, total) { cout << L[i] << " " << R[i] << "\n"; }
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