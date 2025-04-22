#include <bits/stdc++.h>

#include <functional>

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
int ans = 0;
int n, k;
int gr[22][22];
set<piii> ss;
set<int> s1[22][22], s2[22][22];
void dfs1(int x, int y, int v) {
    (v+=gr[x][y])%=k;
    if (x + y == n + 1) s1[x][y].insert(v);
    if (x + 1 <= n) dfs1(x + 1, y, v);
    if (y + 1 <= n) dfs1(x, y + 1, v);
}
// …existing code…

// 1) 把 dfs2 修正为往 s2 插入，并且递归自己

void dfs2(int x, int y, int v) {
    (v += gr[x][y]) %= k;
    if (x + y == n + 1) s2[x][y].insert(v);
    if (x - 1 >= 1) dfs2(x - 1, y, v);
    if (y - 1 >= 1) dfs2(x, y - 1, v);
}

// …existing code…

void work() {
    cin >> n >> k;
    rep(i, 1, n) rep(j, 1, n) cin >> gr[i][j];
    rep(i, 1, n) rep(j, 1, n) gr[i][j] = gr[i][j] * qpow(10, 2 * n - i - j, k) % k;

    // 枚举前半段
    dfs1(1, 1, 0);
    // 枚举后半段
    dfs2(n, n, 0);

    // 2) 前后缀合并
    int L = n - 1;
    vector<int> p10(2 * n, 1);
    rep(e, 1, 2 * n - 2) p10[e] = (long long)p10[e - 1] * 10 % k;
    ans = 0;
    // 只有 x+y==n+1 的格子才是“中点”
    rep(i, 1, n) {
        int j = n + 1 - i;
        auto &P = s1[i][j];
        auto &S = s2[i][j];
        if (P.empty() || S.empty()) continue;
        // 把后缀 set 拷到 vector 并排序
        vector<int> suf(S.begin(), S.end());
        sort(suf.begin(), suf.end());
        for (int pre : P) {
            long long vp = pre * p10[L] % k;  // 前缀左移 L 位
            int need = (k - 1 - vp + k) % k;  // rem ≤ need 保证 vp+rem<k
            auto it = upper_bound(suf.begin(), suf.end(), need);
            if (it != suf.begin()) {
                ans = max(ans, vp + *prev(it));
            }
            // 跨模情况：直接取后缀最大值再 % k
            ans = max(ans, (vp + suf.back()) % k);
        }
    }
    cout << ans << "\n";
}

// …existing code…
// …existing code…

// void work() {
//     cin >> n >> k;
//     // 读入原始格子值
//     static int a[22][22];
//     rep(i, 1, n) rep(j, 1, n) cin >> a[i][j];
//     int L = n - 1;

//     vector<int> p10(2 * n, 1);
//     rep(e, 1, 2 * n - 2) p10[e] = (int)p10[e - 1] * 10 % k;

//     vector<vector<vector<int>>> pref(n + 1, vector<vector<int>>(n + 1));
//     function<void(int, int, int, int)> dfs1 = [&](int x, int y, int rem, int d) {
//         rem = (rem * 10 + a[x][y]) % k;
//         if (d == L) {
//             pref[x][y].push_back(rem);
//             return;
//         }
//         if (x < n) dfs1(x + 1, y, rem, d + 1);
//         if (y < n) dfs1(x, y + 1, rem, d + 1);
//     };
//     dfs1(1, 1, 0, 0);
//     vector<vector<vector<int>>> suf(n + 1, vector<vector<int>>(n + 1));
//     function<void(int, int, int, int)> dfs2 = [&](int x, int y, int rem, int d) {
//         if (d == L) {
//             suf[x][y].push_back(rem);
//             return;
//         }

//         if (x > 1) dfs2(x - 1, y, (rem + a[x][y] * p10[d]) % k, d + 1);
//         if (y > 1) dfs2(x, y - 1, (rem + a[x][y] * p10[d]) % k, d + 1);
//     };
//     dfs2(n, n, 0, 0);

//     ans = 0;

//     rep(i, 1, n) rep(j, 1, n) {
//         auto &P = pref[i][j];
//         auto &S = suf[i][j];
//         if (P.empty() || S.empty()) continue;
//         sort(S.begin(), S.end());
//         for (int pr : P) {
//             int vp = pr * p10[L] % k;

//             int need = (k - 1 - vp + k) % k;
//             auto it = upper_bound(S.begin(), S.end(), need);
//             if (it != S.begin()) {
//                 ans = max(ans, vp + *prev(it));
//             }

//             ans = max(ans, (vp + S.back()) % k);
//         }
//     }

//     cout << ans << "\n";
// }

// …existing code…
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}