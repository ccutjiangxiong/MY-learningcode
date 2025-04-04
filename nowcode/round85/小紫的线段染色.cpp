#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
int n, l;
int x[N], y[N], c[N];
int bi[N];
int lowbit(int x) { return x & -x; }
void update(int x, int v) {
    for (; x <= n * 2; x += lowbit(x)) bi[x] += v;
}
void uprange(int l, int r, int v) {
    update(l, v);
    update(r + 1, -v);
}
int query(int x) {
    int ans = 0;
    for (; x; x -= lowbit(x)) ans += bi[x];
    return ans;
}
map<int, int> mp;
struct pos {
    int x, y, id, se;
    bool operator<(const pos& a) const { return x < a.x; }
} p[N];
void work() {
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        return;
    }
    rep(i, 1, n) cin >> x[i] >> y[i];
    rep(i, 1, n) c[i] = x[i], c[i + n] = y[i];
    sort(c + 1, c + 1 + 2 * n);
    l = unique(c + 1, c + 1 + 2 * n) - c - 1;
    rep(i, 1, l) mp[c[i]] = i;
    rep(i, 1, n) uprange(mp[x[i]], mp[y[i]], 1);
    rep(i, 1, l) if (query(i) > 2) {
        cout << -1 << endl;
        return;
    }
    rep(i, 1, n) p[i] = {x[i], y[i], i};
    sort(p + 1, p + 1 + n);

    // for (int i = 1; i <= n; i += 2) cout << p[i].id << ' ';
    p[1].se = 0;
    int cnt = 0;
    int ma = 1;
    rep(i, 2, n) {
        p[i].se = p[ma].se ^ 1;
        if (p[i].y > p[ma].y) ma = i;
        if (p[i].se) cnt++;
    }
    print(cnt);
    rep(i, 1, n) if (p[i].se) cout << p[i].id << ' ';

    // cout<<
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