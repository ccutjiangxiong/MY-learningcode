#include <bits/stdc++.h>
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
int n, m;
set<pii> s;
int h[N];
void judge(int x, int y) {
    y += (x - 1);
    while (y - n >= 1) y -= n;
    h[y]++;
}
void work() {
    cin >> n >> m;
    rep(i, 1, m) {
        int x, y;
        cin >> x >> y;
        s.emplace(x, y);
    }
    for (auto [x, y] : s) {
        judge(x, y);
    }
    int x = s.size();
    int ans = x * (x - 1) / 2;
    rep(i, 1, 1e6) ans -= h[i] * (h[i] - 1) / 2;
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