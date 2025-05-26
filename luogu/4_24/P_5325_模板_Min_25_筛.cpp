#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define vii vector<pii>
#define viii vector<piii>
#define ep emplace
#define rg ranges
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
int isp[N], pri[N], phi[N], mu[N], d[N], num[N], cnt = 0;
void euler(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i, phi[i] = i - (mu[i] = -(num[i] = 1));
        for (int j = 1, x = 0; j <= cnt && x <= n; j++) {
            x = i * pri[j], isp[x] = 1;
            phi[x] = phi[i] * (pri[j] - (i % pri[j] != 0));
            d[x] = d[i] * 2 * (num[x] = 1);
            mu[x] = i % pri[j] == 0 ? 0 : -mu[i];
            if (i % pri[j] == 0) {
                num[x] = num[i] + 1;
                d[x] = d[i] / num[x] * (num[x] + 1);
                break;
            }
        }
    }
}
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = a * ans % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
// p为质数
int invp(int a, int p) { return qpow(a, p - 2, p); }
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) return a + (x = 1) + (y = 0) - 1;
    int x1, y1;
    int gcd = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return gcd;
}
int invp2(int a, int p) {
    int x = 0, y = 0;
    return exgcd(a, p, x, y) == 1 ? (x % p + p) % p : -1;
}
int ff(int x) {
    return
}
int min25() {
    
}
int ti = 1;
int n;
void work() {
    cin >> n;
    // rep(i, 1, n) {}
    euler(n);
    rep(i, 1, cnt) print(pri[i]);
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