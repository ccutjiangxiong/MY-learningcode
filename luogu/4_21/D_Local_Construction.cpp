#include <bits/stdc++.h>

#include <algorithm>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti;
int n;
void work() {
    cin >> n;
    vi ans(n + 1), p(n + 1);
    rep(i, 1, n) cin >> p[i];
    int m = *rg::max_element(p);
    int l = 1, r = n;
    int t = rg::find(p, -1) - p.begin();
    rep(i, 1, m) {
        vi b[2];
        int x = 0;
        rep(j, 1, n) {
            x |= p[j] == -1;
            if (p[j] == i) b[x].pb(j);
        }
        rg::reverse(b[1]);
        for (int &j : b[0]) ans[j] = i & 1 ? r-- : l++;
        for (int &j : b[1]) ans[j] = i & 1 ? r-- : l++;
    }
    rep(i, 1, n) cout << (ans[i] ? ans[i] : l) << " \n"[i == n];
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