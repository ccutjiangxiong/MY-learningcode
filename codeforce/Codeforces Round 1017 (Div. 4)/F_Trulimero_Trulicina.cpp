#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define vi vector<int>
#define pb emplace_back
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
int n, m, k;
void work() {
    cin >> n >> m >> k;
    int cnt = 0;
    int x = n * m / k;
    // print(n, m, k);
    vector<vector<int>> gr(n + 1, vector<int>(m + 1));
    if (n >= m) {
        rep(i, 1, n) rep(j, 1, m) if ((i & 1) == (j & 1)) gr[i][j] = cnt / x + 1, cnt++;
        rep(i, 1, n) rep(j, 1, m) if ((i & 1) != (j & 1)) gr[i][j] = cnt / x + 1, cnt++;
    } else {
        rep(j, 1, m) rep(i, 1, n) if ((i & 1) == (j & 1)) gr[i][j] = cnt / x + 1, cnt++;
        rep(j, 1, m) rep(i, 1, n) if ((i & 1) != (j & 1)) gr[i][j] = cnt / x + 1, cnt++;
    }
    rep(i, 1, n) rep(j, 1, m) cout << gr[i][j] << " \n"[j == m];
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