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
int n, m;
int fa[N];
struct hay {
    int x, y, z;
} e[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }

void work() {
    cin >> n >> m;
    rep(i, 1, m) cin >> e[i].x >> e[i].y >> e[i].z;
    sort(e + 1, e + 1 + m, [](hay u, hay v) { return u.z < v.z; });
    int ans = 0;
    rep(i, 1, n) fa[i] = i;
    rep(i, 1, m) if (find(e[i].x) != find(e[i].y)) { uni(e[i].x, e[i].y), ans = e[i].z; };
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