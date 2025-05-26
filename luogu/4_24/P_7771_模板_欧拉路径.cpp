#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fr first
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

int ti = 1, n, m, d[N], de[N];
vi e[N];
set<int> ss[N];
stack<int> st;
void dfs(int u) {
    for (int i = de[u]; i < e[u].size(); i = de[u]) {
        de[u] = i + 1;
        dfs(e[u][i]);
    }
    st.push(u);
}
void work() {
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        e[u].pb(v);
        d[u]++, d[v]--;
    }
    rep(i, 1, n) rg::sort(e[i]);
    map<int, int> mp;
    int fl = 1, s = 0, t = 0;
    rep(i, 1, n) {
        mp[d[i]]++;
        if (d[i] == 1) s = i;
        if (d[i] == -1) t = i;
    }

    for (auto [u, k] : mp) {
        if (abs(u) > 1 || (abs(u) == 1 && k != 1)) fl = 0;
    }
    if (!fl || s + t == 1) {
        print("No");
        return;
    }
    if (s + t == 0)
        dfs(1);
    else
        dfs(s);
    while (st.size()) {
        cout << st.top() << ' ';
        st.pop();
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