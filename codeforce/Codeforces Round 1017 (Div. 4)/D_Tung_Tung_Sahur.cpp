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
string s, p;
void work() {
    cin >> p >> s;
    vector<int> q1, q2;
    int cnt = 0;
    p += '&';
    s += '%';
    rep(i, 0, p.size() - 1) {
        if (i && p[i] != p[i - 1]) q1.pb(cnt), cnt = 0;
        cnt++;
    }
    cnt = 0;
    rep(i, 0, s.size() - 1) {
        if (i && s[i] != s[i - 1]) q2.pb(cnt), cnt = 0;
        cnt++;
    }
    // for (int x : q2) print(x);
    int ans = (q1.size() == q2.size()) && p[0] == s[0];
    if (ans) {
        rep(i, 1, q1.size()) {
            // print(q1[i - 1], q2[i - 1]);
            if (q1[i - 1] * 2 < q2[i - 1] || q1[i - 1] > q2[i - 1]) ans = 0;
        }
    }
    if (ans)
        print("YES");
    else
        print("NO");
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