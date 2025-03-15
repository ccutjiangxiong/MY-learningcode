#include <bits/stdc++.h>

#include <cmath>

#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, N2 = 2222, N5 = 5555;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int in() {
    int x;
    return (cin >> x, x);
}
int ti = 1;
int n, m, q;
int a[N];
int x;
vector<int> e[N];
int fa[N], b[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }
int f[N][33];
void st(const int a[], int n) {
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}
int ask(int a, int b) {
    int j = log2(b - a + 1);
    int ans = max(f[a][j], f[b - (1 << j) + 1][j]);
    return ans;
}

void work() {
    int n, m, q;
    cin >> n >> m >> q;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) fa[i] = i;
    rep(i, 1, m) uni(in(), in());
    rep(i, 1, n - 1) find(i) == find(i + 1) ? b[i] = 0 : b[i] = inf;

    st(b, n);
    // print(ask(1, 4));
    rep(i, 1, q) {
        int x, y;
        cin >> x >> y;
        if(x==y) cout<<0<<endl
        else if (ask(x, y - 1) == inf)
            cout << -1 << endl;
        else
            cout << 1 << endl;
    }
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