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
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v);
    edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;
int n, a[N];
vi e[N];

int dp0[N], dp1[N];

void work() {
    cin >> n;
    int sa = 0;
    rep(i, 1, n) {
        cin >> a[i];
        sa += a[i];
        e[i].clear();
    }
    rep(i, 1, n - 1) be(e);

    static int p[N], idx[N];
    vector<int> order;
    order.reserve(n);
    stack<int> stk;
    stk.push(1);
    p[1] = 0;
    rep(i, 1, n) idx[i] = 0;

    while (!stk.empty()) {
        int u = stk.top();
        if (idx[u] < (int)e[u].size()) {
            int v = e[u][idx[u]++];
            if (v == p[u]) continue;
            p[v] = u;
            stk.push(v);
        } else {
            stk.pop();
            order.push_back(u);
        }
    }

    for (int u : order) {
        int s = 0;
        vector<int> g;
        for (int v : e[u])
            if (v != p[u]) {
                s += dp0[v];
                int gain = dp1[v] + a[u] + a[v] - dp0[v];
                if (gain > 0) g.pb(gain);
            }
        sort(g.begin(), g.end(), greater<int>());
        int g0 = g.size() > 0 ? g[0] : 0;
        int g1 = g.size() > 1 ? g[1] : 0;
        dp1[u] = s + g0;
        dp0[u] = s + g0 + g1;
    }

    int ans = 2 * sa - dp0[1];
    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}