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

int ti;
int n, k, c[N];
void work() {
    vector<int> h[3];
    map<int, int> mp;
    me(c, 0);
    int ans = 0;
    cin >> n >> k;
    rep(i, 1, n) {
        int a, b;
        cin >> a >> b;
        // [i]
        mp[i] += b;
        if (b < 3)
            ans += b;
        else
            h[b % 3].pb(b);
    }
    // rep(i, 1, n) {
    //     if (mp[i] < 3)
    //     ans +=mp[i] ;
    //     else
    //     h[mp[i] % 3].pb(mp[i]);
    // }
    for (int &x : h[2]) {
        if (k)
            k--, ans += 5, x -= 5;
        else
            ans += 2;
        if (x) h[0].pb(x);
    }
    for (int &x : h[1]) {
        if (k)
            ans += 4, x -= 4, k--;
        else
            ans += 2;
        if (x) h[0].pb(x);
    }
    for (int &x : h[0])
        if (k)
            ans += 3 * min(x / 3, k), k -= min(x / 3, k);
        else
            ans += 2;

    if (k)
        cout << -1 << endl;
    else
        cout << ans << endl;
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