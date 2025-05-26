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

int ti, n, m;
char gr[1111][1111], c[1111], r[1111];
void work() {
    cin >> n >> m;
    int cnt = 0;
    set<int> s1, s2;
    rep(i, 1, 1110) c[i] = r[i] = 0;
    int f1 = 0, f2 = 0, a = 0, b = 0;
    rep(i, 1, n) rep(j, 1, m) {
        cin >> gr[i][j];
        if (gr[i][j] == '1') s1.ep(i), s2.ep(j), cnt++, r[i]++, c[j]++;
    }

    // print(a, b);
    int ans = 0;
    if (cnt == 0) ans = 1;
    int cr = 0, cc = 0;
    rep(i, 1, n) cr += (r[i] == m);
    rep(i, 1, m) cc += (c[i] == n);
    // if (s1.size() == 2 && cnt == 2 * m) ans = 1;
    // if (s2.size() == 2 && cnt == 2 * n) ans = 1;
    if (cr == 2 && cnt == 2 * m) ans = 1;
    if (cc == 2 && cnt == 2 * n) ans = 1;
    rep(i, 1, n) rep(j, 1, m) {
        if (gr[i][j] == '0' && r[i] == m - 1 && c[j] == n - 1 && cnt == n + m - 2) ans = 1;
    }
    print(ans ? "YES" : "NO");
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