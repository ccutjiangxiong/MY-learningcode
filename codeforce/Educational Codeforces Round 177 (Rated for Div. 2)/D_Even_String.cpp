#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 998244353, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T> void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
int n;
int h[33];
int isp[N],pri[N],cnt=0;
void euler(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isp[i])
            pri[++cnt] = i;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}
int fplus(int a, int b, int mod) {
    int ans = 0;
    while (b) {
        if (b & 1)
            ans = (ans + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ans;
}
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1)
            ans = a * ans % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
// p为质数
int invp(int a, int p) {
    return qpow(a, p - 2, p);
}
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0)
        return a + (x = 1) + (y = 0) - 1;
    int x1, y1;
    int gcd = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return gcd;
}
int invp2(int a, int p) {
    int x = 0, y = 0;
    return exgcd(a, p, x, y) == 1 ? (x % p + p) % p : -1;
}
int f[N], g[N], s[50010][210], de[N];
int getc(int n, int m, int p) { return f[n] * g[m] % p * g[n - m] % p; }
void initc(int n, int p) {
  f[0] = 1, g[0] = invp(f[0], p);
  rep(i, 1, n) f[i] = f[i - 1] * i % p, g[i] = invp(f[i], p);
}
void inits1(int n, int m, int p) {
  s[0][0] = 1;
  rep(i, 1, n) rep(j, 1, m) s[i][j] =
      (s[i - 1][j - 1] + s[i - 1][j] * (i - 1)) % p;
}
void inits2(int n, int m, int p) {
  s[0][0] = 1;
  rep(i, 1, n) rep(j, 1, m) s[i][j] =
      (s[i - 1][j - 1] + s[i - 1][j] * j) % p;
}
void initd(int n, int p) {
  de[1] = 0, de[2] = 1;
  rep(i, 3, n) (de[i] = (i - 1) * (de[i - 1] + de[i - 2])) %= p;
}
int lucas(int n, int m, int p) {
  return m == 0 ? 1 : lucas(n / p, m / p, p) * getc(n % p, m % p, p) % p;
}
int catalan(int n, int m, int p) { return (getc(n + m, n, p) - getc(n + m, n - 1, p) + p) % p; }
void work() {
    rep(i, 1, 26) cin >> h[i];
    int su = 0;
    rep(i, 1, 26) su += h[i];

    int odd = (su + 1) / 2, even = su - odd;

   
    vector<int> dp(odd + 1, 0), ndp(odd + 1, 0);
    dp[0] = 1;
    rep(i, 1, 26) {
        ndp.assign(odd + 1, 0);
        if (h[i] == 0) {
            for (int j = 0; j <= odd; j++) {
                ndp[j] = (ndp[j] + dp[j]) % mod;
            }
        } else {
            for (int j = 0; j <= odd; j++) {
                if (dp[j]) {
                 
                    ndp[j] = (ndp[j] + dp[j]) % mod;

                    if (j + h[i] <= odd) ndp[j + h[i]] = (ndp[j + h[i]] + dp[j]) % mod;
                }
            }
        }
        dp = ndp;
    }
    int ways = dp[odd] % mod;  


    initc(su, mod);
    int ar = (f[odd] * f[even]) % mod;

    int denom = 1;
    rep(i, 1, 26) { denom = (denom * f[h[i]]) % mod; }
    int d_i = qpow(denom, mod - 2, mod);
    int ans = ((ways * ar) % mod * d_i) % mod;
    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}