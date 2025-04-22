#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>

#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 998244353, inf = 1e18 + 3;
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
int n, x, m, k, a[N];
int isp[N], pri[N], Phi[N], cnt = 0;
void euler(int n) {
    Phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i, Phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
            Phi[i * pri[j]] = Phi[i] * (pri[j] - (i % pri[j] != 0));
            if (i % pri[j] == 0) break;
        }
    }
}
int fplus(int a, int b, int mod) {
    int ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ans;
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
int f[N], g[N], s[50010][210], de[N];
int getc(int n, int m, int p) { return f[n] * g[m] % p * g[n - m] % p; }
void initc(int n, int p) {
    f[0] = 1, g[0] = invp(f[0], p);
    rep(i, 1, n) f[i] = f[i - 1] * i % p, g[i] = invp(f[i], p);
}
void inits1(int n, int m, int p) {
    s[0][0] = 1;
    rep(i, 1, n) rep(j, 1, m) s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * (i - 1)) % p;
}
void inits2(int n, int m, int p) {
    s[0][0] = 1;
    rep(i, 1, n) rep(j, 1, m) s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % p;
}
void initd(int n, int p) {
    de[1] = 0, de[2] = 1;
    rep(i, 3, n)(de[i] = (i - 1) * (de[i - 1] + de[i - 2])) %= p;
}
int lucas(int n, int m, int p) {
    return m == 0 ? 1 : lucas(n / p, m / p, p) * getc(n % p, m % p, p) % p;
}
int catalan(int n, int m, int p) { return (getc(n + m, n, p) - getc(n + m, n - 1, p) + p) % p; }
int kk[N];
void work() {
    cin >> n >> x >> m >> k;
    int k2 = qpow(2, k, mod);
    rep(i, 1, n) cin >> a[i];
    int g = 1;
    while (g <= m) g <<= 1;
    int ans = 0;
    initc(1e6 + 5, mod);
    rep(i, 0, k) kk[i] = getc(k, i, mod);
    rep(i, 1, n) {
        int f = a[i], fl = 0;
        int s = 0;
        int la=0;
        deque<int> h;
        set<int> st;
        rep(j, 0, k) {
            print(f-la);
            int u = (f % g) & m;
            // if (la == f) {
            //     (ans += (k2 + mod - s) * la) %= mod;
            //     break;
            // }
            if (st.contains(u)) {
                (ans += (k2 + mod - s) * la) %= mod;
                while(h.front()!=u) h.pop_front();
                int tot=accumulate(h.begin(), h.end(), 0ll);
                ans+=()
            }
            la=f;
            (ans += kk[j] * f) %= mod, f = f + (f & m) + x;
            (s += kk[j]) %= mod;
            h.pb(u);
            st.insert(u);
        }
    }
    cout << ans * invp(qpow(2, k, mod), mod) % mod << endl;
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