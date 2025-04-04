#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 1e5 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
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
int n, m;
int k[N], ask[N];
vector<pii> q1, q2;
int vis[N], ink[N];
map<piii, bool> vin;
vector<pii> ans[N], ans2[N];
int cnt = 0;
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

inline void wt(const char* s) {
    while (*s) putchar(*s++);
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
set<int> ss;
int hh;
int u, v;
int h[N];
void dfs(int x, int u, int v) {
    if (!vis[u * v]++ && ink[u * v]) {
        ans[u * v] = q1, ans2[u * v] = q2;
        ss.erase(u * v);
    }
    if (vin[{x, max(u, v), min(v, u)}] || ss.empty() || x > n) return;
    vin[{x, max(u, v), min(u, v)}] = 1;
    rep(i, 1, n) rep(j, 0, h[k[x]]) rep(p, 0, h[k[x]] - j) {
        if (ss.size() && (u + j * k[x]) * (v + p * k[x]) <= *ss.rbegin() &&
            max(u + j * k[x], v + p * k[x]) <= *ss.rbegin()) {
            if (j) q1.emplace_back(k[x], j);
            if (p) q2.emplace_back(k[x], p);
            dfs(x + 1, u + j * k[x], v + p * k[x]);
            if (j) q1.pop_back();
            if (p) q2.pop_back();
        }
    }
}

void work() {
    nrd(n, m);
    rep(i, 1, n) k[i] = rd();
    rep(i, 1, n) h[k[i]]++;
    sort(k + 1, k + 1 + n);
    n = unique(k + 1, k + 1 + n) - k - 1;
    rep(i, 1, m) ask[i] = rd();
    rep(i, 1, m) ink[ask[i]] = 1, ss.insert(ask[i]);
    sort(k + 1, k + 1 + n);
    dfs(1, 0, 0);
    rep(i, 1, m) {
        if (vis[ask[i]]) {
            int x1 = 0, x2 = 0;
            for (auto [x, y] : ans[ask[i]]) x1 += y;
            for (auto [x, y] : ans2[ask[i]]) x2 += y;
            wt("Yes");
            putchar('\n');
            wt(x1);
            putchar(' ');
            wt(x2);
            putchar('\n');
            for (auto [x, y] : ans[ask[i]]) rep(j, 1, y) wt(x), putchar(' ');
            putchar('\n');
            for (auto [x, y] : ans2[ask[i]]) rep(j, 1, y) wt(x), putchar(' ');
            putchar('\n');
        } else {
            wt("No");
            putchar('\n');
        }
    }
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}