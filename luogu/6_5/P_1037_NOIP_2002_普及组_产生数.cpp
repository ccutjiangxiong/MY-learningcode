#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
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
using ull = uint64_t;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti=1 ,n,m,k,a[N],b[N],c[N],ans,res,cnt,x,y,z;
vi e[N];

// ...existing code...
void work() {
    string s;
    int k;
    cin >> s >> k;
    vector<vector<int>> adj(10);
    rep(i, 1, k) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
    }
    // precompute reachable digits for 0..9
    vector<set<int>> reach(10);
    rep(d, 0, 9) {
        queue<int> q;
        vector<bool> vis(10, false);
        vis[d] = true;
        q.push(d);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            reach[d].insert(u);
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    // big-integer result as decimal string
    string ans = "1";
    for (char ch : s) {
        int d = ch - '0';
        int cnt = reach[d].size();  // number of options for this digit
        int carry = 0;
        for (int i = sz(ans) - 1; i >= 0; i--) {
            int prod = (ans[i] - '0') * cnt + carry;
            ans[i] = char('0' + prod % 10);
            carry = prod / 10;
        }
        while (carry) {
            ans.insert(ans.begin(), char('0' + carry % 10));
            carry /= 10;
        }
    }
    cout << ans << "\n";
}
// ...existing code...
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}