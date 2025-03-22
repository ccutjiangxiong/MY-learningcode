#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
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
int ti;
int n;
int p[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }

void work() {
    vector<piii> e;
    cin >> n;
    rep(i, 1, n) cin >> p[i];
    sort(p + 1, p + 1 + n);
    n = unique(p + 1, p + 1 + n) - p - 1;
    int mx = p[n];
    rep(i, 1, n) fa[i] = i;
    rep(i, 1, n - 1) {
        int k = p[i];
        while (k <= mx) {
            int y = lower_bound(p + 1, p + 1 + n, k) - p + (k == p[i]);
            e.emplace_back(p[y] % p[i], i, y);
            k += p[i];
        }
    }
    ranges::sort(e);
    int cnt = 0, ans = 0;
    for (auto [w, u, v] : e) {
        if (find(u) != find(v)) uni(u, v), cnt++, ans += w;
        if (cnt == n - 1) break;
    }
    cout << ans << endl;
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