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

int ti, n, m, k;
char a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];
string s;
void work() {
    set<int> gr[3][3];
    cin >> n >> m >> s;
    rep(i, 1, m) cin >> a[i] >> b[i], gr[a[i] - 'a'][b[i] - 'a'].ep(i);
    for (char &ch : s) {
        if (ch == 'b') {
            if (gr[1][0].size())
                ch = 'a', gr[1][0].erase(gr[1][0].begin());
            else if (gr[1][2].size() && gr[2][0].size()) {
                int x = *gr[1][2].begin();
                auto y = gr[2][0].lower_bound(x);
                if (y != gr[2][0].end()) gr[1][2].erase(x), gr[2][0].erase(y), ch = 'a';
            }
        }
        if (ch == 'c') {
            if (gr[2][0].size())
                ch = 'a', gr[2][0].erase(gr[2][0].begin());
            else if (gr[2][1].size() && gr[1][0].size()) {
                int x = *gr[2][1].begin();
                auto y = gr[1][0].lower_bound(x);
                if (y != gr[1][0].end()) gr[2][1].erase(x), gr[1][0].erase(y), ch = 'a';
            }
            if (ch == 'c' && gr[2][1].size()) gr[2][1].erase(gr[2][1].begin()), ch = 'b';
        }
    }
    pt(s);
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