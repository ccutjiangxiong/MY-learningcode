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
vector<int> q1, q2;
int vis[N], ink[N];
map<piii, bool> vin;
vector<int> ans[N], ans2[N];
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
void dfs(int x, int u, int v) {
    if (!vis[u * v]++ && ink[u * v]) {
        ans[u * v] = q1, ans2[u * v] = q2;
        ss.erase(u * v);
    }
    if (vin[{x, max(u, v), min(v, u)}] || ss.empty() || x > n) return;
    vin[{x, max(u, v), min(u, v)}] = 1;
    int f = 0;
    if (u < v) swap(u, v), swap(q1, q2), f = 1;
    if (ss.size() && u * (v + k[x]) <= *ss.rbegin() && v + k[x] <= *ss.rbegin()) {
        q1.push_back(k[x]);
        dfs(x + 1, u, v + k[x]);
        q1.pop_back();
    }
    if (ss.size() && v * (u + k[x]) <= *ss.rbegin() && u + k[x] <= *ss.rbegin()) {
        q2.push_back(k[x]);
        dfs(x + 1, u + k[x], v);
        q2.pop_back();
    }
    dfs(x + 1, u, v);
    if (f) swap(u, v), swap(q1, q2);
}

void work() {
    nrd(n, m);
    rep(i, 1, n) k[i] = rd();
    rep(i, 1, m) ask[i] = rd();
    rep(i, 1, m) ink[ask[i]] = 1, ss.insert(ask[i]);
    sort(k + 1, k + 1 + n);
    dfs(1, 0, 0);
    rep(i, 1, m) {
        if (vis[ask[i]]) {
            wt("Yes");
            putchar('\n');
            wt(ans[ask[i]].size());
            putchar(' ');
            wt(ans2[ask[i]].size());
            putchar('\n');
            for (int x : ans[ask[i]]) wt(x), putchar(' ');
            putchar('\n');
            for (int x : ans2[ask[i]]) wt(x), putchar(' ');
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