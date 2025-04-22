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
using namespace numbers;

void be(int u, int v, auto e[N]) {
    cin >> u >> v;
    e[u].pb(v), e[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;
int n, m;
int A[2323][2322];
vector<int> b[N];
int ans[4444][1111];

void work() {
    int res = 0;
    me(ans, 0);
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> A[i][j];
    rep(i, 1, n) rep(j, 1, m) {
        ans[i - j + 3000][A[i][j]]++;
        ans[i + j][A[i][j]]++;
    }
    rep(i, 1, 4000) rep(j, 1, 1110) res += ans[i][j] * (ans[i][j] - 1) / 2;
    cout << res * 2 << endl;
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