#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
// int df;
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n,m = 222;
int x[N], y[N], c[N], sa[N], rk[N], h[N];
string s;
void Sa() {
    rep(i, 1, n) c[x[i] = s[i - 1]]++;
    rep(i, 1, m) c[i] += c[i - 1];
    rem(i, n, 1) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        memset(c, 0, sizeof(c));
        rep(i, 1, n) y[i] = sa[i];
        rep(i, 1, n) c[x[y[i] + k]]++;
        rep(i, 1, m) c[i] += c[i - 1];
        rem(i, n, 1) sa[c[x[y[i] + k]]--] = y[i];
        memset(c, 0, sizeof(c));
        rep(i, 1, n) y[i] = sa[i];
        rep(i, 1, n) c[x[y[i]]]++;
        rep(i, 1, m) c[i] += c[i - 1];
        rem(i, n, 1) sa[c[x[y[i]]]--] = y[i];
        rep(i, 1, n) y[i] = x[i];
        m = 0;
        for (int i = 1; i <= n; i++)
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = m;
            else
                x[sa[i]] = ++m;
        if (m == n) break;
    }
    rep(i, 1, n) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 1) continue;
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k - 1] == s[j + k - 1]) k++;
        h[rk[i]] = k;
    }
}
int f[N], g[N];
int u;
bool judge() {
    rep(i, 1, u) if (!f[i]) return false;
    return true;
}
void work() {
    cin >> u;
string t;
    rep(i, 1, u) {
        cin >> t;
        f[i] = t.size();
        s += t;
        n += f[i];
        g[i] = g[i - 1] + f[i];
    }
    Sa();
    // print(s);
    rep(i, 1, n) cout << sa[i] << ' ';
    cout << endl;
    rep(i, 1, n) cout << h[i] << ' ';
    cout << endl;
    int r = 1;
    int mi = inf;
    int ans = 0;
    rep(i, 1, n) f[i] = 0;
    rep(st, 1, n) {
        while (!judge()) {
            r++;
            rep(i, 1, u) if (sa[r] > g[i - 1] && sa[r] <= g[i]) f[i]--;
            mi = min(mi, h[r]);
        }
        ans = max(ans, mi);
        rep(i, 1, u) if (sa[st] > g[i - 1] && sa[st] <= g[i]) f[i]--;
    }
    cout << ans << endl;
    // print(ans, p1, p2);
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