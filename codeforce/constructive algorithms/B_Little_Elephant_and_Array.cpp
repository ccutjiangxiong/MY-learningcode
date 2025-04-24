#include <bits/stdc++.h>
// #define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define vii vector<pii>
#define viii vector<piii>
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 1e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
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

int ti = 1;
int n, m, a[N], tot[N], pre[500][100005], val[N];
void work() {
    vi h;
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) if (a[i] <= n) tot[a[i]]++;
    int cnt = 0;
    rep(i, 1, n) if (tot[i] >= i) {
        h.pb(i);
        val[++cnt] = i;
        rep(j, 1, n) pre[val[i]][j] = pre[val[i]][j - 1] + (a[j] == i);
    }
    rep(i, 1, m) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int x : h) ans += (pre[val[x]][r] - pre[val[x]][l - 1] == x);

        print(ans);
    }
}

signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}