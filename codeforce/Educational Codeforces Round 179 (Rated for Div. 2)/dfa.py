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
int gr[3][3];
void work() {
    cin >> n >> m;
    string s;
    cin >> s;
    me(gr, 0);
    rep(i, 1, m) cin >> a[i] >> b[i], gr[a[i] - 'a'][b[i] - 'a']++;
    int cur = 0, p = 1;
    int a1 = 0, a2 = 0;
    for (char &ch : s) {
        if (ch == 'b' && gr[1][0]) ch = 'a', gr[1][0]--,a1++;
        if (ch == 'c' && gr[2][0]) ch = 'a', gr[2][0]--,a2++;
    }
    pt(s);
    
    if (gr[2][0]) {
        int t = 0, ans = 0;
        rep(i, 1, m) if (a[i] == 'b' && b[i] == 'c') t++;
        else if (a[i] == 'c' && b[i] == 'a' && (a2-- <= 0) && t) t--, ans++;
        for (char &ch : s)
            if (ch == 'b' && ans) ans--, ch = 'a';
    } else {
        int t = 0, ans = 0;
        rep(i, 1, m) if (a[i] == 'c' && b[i] == 'b') t++;
        else if (a[i] == 'b' && b[i] == 'a' && (a1-- <= 0) && t) t--, ans++;
        for (char &ch : s)
            if (ch == 'c') {
                if (ans)
                    ch = 'a', ans--;
                else if (t)
                    ch = 'b', t--;
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