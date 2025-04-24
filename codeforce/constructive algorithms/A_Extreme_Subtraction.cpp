#include <bits/stdc++.h>
#define int long long
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
int n, a[N], pre[N], suf[N];
void work() {
    cin >> n;
    int y = 0, mi = inf, cnt = 0;
    rep(i, 1, n) cin >> a[i], mi = min(mi, a[i]), pre[i] = mi;
    suf[n + 1] = inf;
    rem(i, n, 1) suf[i] = min(suf[i + 1], a[i]);
    rep(i, 1, n) y += (a[i] - max(pre[i], suf[i]));
    print(y <= mi ? "YES" : "NO");
}
void work1() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int x = 0, y = 0, t = 0;
    rep(i, 2, n) {
        t = a[i] - a[i - 1];
        if (t > 0)
            y += t;
        else
            x += -t;
    }
    print(x <= a[1] && y <= a[n] ? "YES" : "NO");
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