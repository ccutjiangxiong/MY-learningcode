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
int a, b, c, d;
void work() {
    cin >> a >> b >> c >> d;
    string s;
    cin >> s;
    int ans = 1;
    vector<int> v[4];

    int n = s.size();
    int f = (s[0] == 'A') ? 0 : 1, cnt = 1;
    rep(i, 1, n - 1) {
        if (s[i] != s[i - 1])
            cnt++;
        else {
            if (cnt > 1) v[f].pb(cnt), cnt = 1;
            f = (s[i] == 'A') ? 0 : 1;
        }
    }
    if (cnt > 1) v[f].pb(cnt);
    int x = count(s.begin(), s.end(), 'A'), y = count(s.begin(), s.end(), 'B'), z = 0;
    if (x != a + d + c || y != b + d + c) ans = 0;
    rep(j, 0, 1) for (int x : v[j]) {
        if (x & 1)
            z += x / 2;
        else
            v[j + 2].pb(x);
    }
    ranges::sort(v[2]);
    ranges::sort(v[3]);
    for (int x : v[2]) {
        int t = min(c, x / 2);
        if (c) c -= t, x -= 2 * t;
        if (x) z += (x - 1) / 2;
    }
    for (int x : v[3]) {
        int t = min(d, x / 2);
        if (d) d -= t, x -= 2 * t;
        if (x) z += (x - 1) / 2;
    }
    if (c + d > z) ans = 0;
    cout << (ans ? "YES" : "NO") << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    // return 0;
}