#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 998244353, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int t, k, n;
int ans[N];
int pri[N];
int isp[N], ask[N], d[N];
int cnt = 0;
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = a * ans % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
int inv[N];
char buf[1 << 21], *p1 = buf, *p2 = buf;
char gc() {
    if (p1 == p2) {
        size_t bytesRead = fread(buf, 1, 1 << 21, stdin);
        p2 = buf + bytesRead;
        p1 = buf;
        if (bytesRead == 0) return EOF;
    }
    return *p1++;
}
inline int rd() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f *= -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }
    return x * f;
}
inline void wt(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) wt(x / 10);
    putchar(x % 10 + '0');
}
template <typename... T>
void nrd(T&... a) {
    ((a = rd()), ...);
}
template <typename... T>
void nwt(T... a) {
    ((wt(a), putchar(' ')), ...);
    putchar('\n');
}
void work() {
    // cin >> t >> k >> n;
    t = rd();
    k = rd();
    n = rd();
    rep(i, 1, t) ask[i] = rd();
    rep(i, 1, n) d[ask[i]] = 1;

    rep(i, 2, n) {
        int x = i;
        rep(j, 1, cnt) while (x % isp[j] == 0) x /= isp[j], pri[j]++;
        if (x > 1) isp[++cnt] = x, pri[cnt]++, inv[isp[cnt]] = qpow(isp[cnt], k, mod);
        if (d[i]) rep(j, 1, cnt) if (pri[j] & 1)(ans[i] += inv[isp[j]]) %= mod;
    }
    rep(i, 1, t) {
        if (ask[i] == 1)
            // cout << 0 << '\n';
            wt(0), putchar('\n');
        else
            wt(ans[ask[i]]), putchar('\n');
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) ti = rd();
    while (ti--) {
        work();
    }
    return 0;
}