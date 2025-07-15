#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;

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
int n, m = 222;
int f[N][33];
int x[N], y[N], c[N], sa[N], rk[N], h[N];
string s;
void Sa(string s) {
    m = 222;
    me(c, 0);
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
void st(const int a[], int n) {
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

int ask(int a, int b, int f[N][33]) {
    int j = log2(b - a + 1);
    int ans = min(f[a][j], f[b - (1 << j) + 1][j]);
    return ans;
}
int f1[N][33], f2[N][33];
int rk1[N], rk2[N];
void prest(string s) {
    int n = s.size();
    Sa(s);
    rep(i, 1, n) rk1[i] = rk[i];
    st(h, n);
    rep(i, 1, n) rep(j, 0, 32) f1[i][j] = f[i][j];
    rg::reverse(s);
    Sa(s);
    st(h, n);
    rep(i, 1, n) rep(j, 0, 32) f2[i][j] = f[i][j];
}
int ti;
vi e[N];
int h1[N], h2[N];
int df[N], dg[N];
// void work() {
void work() {
    cin >> s;
    n = s.size();
    prest(s);
    // 清零差分数组
    me(df, 0);
    me(dg, 0);

    // 枚举 Len 作为 A、B 的长度
    for (int Len = 1; Len * 2 <= n; Len++) {
        for (int i = Len; i + Len <= n; i += Len) {
            int j = i + Len;
            // 正向 LCP 最多 Len
            int a1 = min(rk1[i], rk1[j]), b1 = max(rk1[i], rk1[j]);
            int Lcp = min(ask(a1, b1, f1), Len);
            // 反向 LCS 最多 Len-1
            int x = n - i + 1, y = n - j + 1;
            int a2 = min(rk2[x], rk2[y]), b2 = max(rk2[x], rk2[y]);
            int Lcs = min(ask(a2, b2, f2), Len - 1);
            if (Lcp + Lcs >= Len) {
                int t = Lcp + Lcs - Len + 1;
                // A 段结束位置 p ∈ [i - Lcs, i - Lcs + t - 1]
                int a_pos = i - Lcs;
                dg[a_pos] += 1;
                dg[a_pos + t] -= 1;
                // B 段起始位置 q = p + 1 ∈ [j + Lcp - t, j + Lcp - 1]
                int b_pos = j + Lcp - t;
                df[b_pos] += 1;
                df[b_pos + t] -= 1;
            }
        }
    }

    // 前缀和还原
    rep(i, 1, n) {
        dg[i] += dg[i - 1];
        df[i] += df[i - 1];
    }

    // 累加所有分割点 k 的 dg[k] * df[k+1]
    long long ans = 0;
    for (int k = 1; k < n; k++) {
        ans += dg[k] * df[k + 1];
    }
    print(ans);
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