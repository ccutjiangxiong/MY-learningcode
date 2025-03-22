#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n;
pii p[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }
vector<int> q;
set<int> h;
int fl = 0;
void work() {
    cin >> n;
    rep(i, 1, n) cin >> p[i].first >> p[i].second;
    sort(p + 1, p + 1 + n);
    rep(i, 1, n) fa[i] = i, fa[i + n] = i + n;
    int my = 0;
    rep(i, 1, n) {
        if (p[i].first > my) {
            q = vector<int>(), uni(1, i), uni(1 + n, i + n);
        } else
            for (int x : q)
                if (p[i].first <= p[x].second) {
                    if (find(i) == find(x) || find(i + n) == find(x + n)) fl = 1;
                    uni(i + n, x), uni(i, x + n);
                }
        my = max(my, p[i].second);
        q.push_back(i);
    }
    for (int x : q)
        if (x <= n) h.insert(x);
    if (fl)
        cout << -1 << endl;
    else {
        int ans = 0;
        rep(i, 1, n) if (find(i) == 1 || find(i + n) == n + 1) ans++;
        cout << ans << endl;
        rep(i, 1, n) if (find(i) == 1 || find(i + n) == n + 1) cout << i << ' ';
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