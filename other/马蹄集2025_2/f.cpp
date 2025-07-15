#pragma optimize(3)
#include <bits/stdc++.h>
// #define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define pb emplace_back
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 1e6 + 6, inf = 1e18, mod = 1e9 + 7;
int ti = 1;
int a[N];
int n, m;
int f[N][33];
void st(const int a[], int n) {
    rep(i, 1, n) f[i][0] = a[i];
    for (int j = 1; (1ll << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
}
int ask(int a, int b) {
    int j = log2(b - a + 1);
    int ans = max(f[a][j], f[b - (1 << j) + 1][j]);
    return ans;
}
vi ss[N];
void work() {
    string s;
    cin >> s;
    int n = s.size();
    int u1 = 0, u2 = 0;
    rep(i, 1, n) {
        if (s[i - 1] == '(')
            u1++;
        else
            u2++;
        a[i] = u1 - u2;
    }
    st(a, n);
    u1 = u2 = 0;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        char ch = s[i - 1];
        if (ch == '(')
            u1++;
        else
            u2++;
        int res = 0;
        if (ch == ')') {
            for (int x : ss[u1 - u2 + 1]) {
                int h = ask(x, i);
                res += ask(x, i) - a[x] + 1;
            }
        }
        if (ch == '(') ss[u1 - u2].pb(i);
        ans += res;
    }
    cout << ans << endl;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}