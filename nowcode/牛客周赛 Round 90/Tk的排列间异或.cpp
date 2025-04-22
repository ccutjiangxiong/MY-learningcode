#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
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

int ti = 1;
int n;
int fun(int x, int n) {
    // if (n == 3) {
    //     if (x == 1) return 2;
    //     if (x == 2) return 1;
    //     return 3;
    // }
    int k = 1;
    while (k * 2 <= n) k <<= 1;
    // if (x == n) return x;
    if (2 * k - x > n) return fun(x, 2 * k - n - 1);
    return 2 * k - x;
}
void work() {
    cin >> n;
    rep(i, 1, n) {
        int x;
        cin >> x;
        cout << fun(x, n) << ' ';
    }
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