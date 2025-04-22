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

int ti=1;
int n, m;
void work() {
    cin >> n >> m;
    vector<vi> adj(n + 1);
    vector<int> cnt(m);
    rep(i, 0, m - 1) {
        int k;
        cin >> k;
        cnt[i] = k;
        rep(j, 1, k) {
            int a;
            cin >> a;
            adj[a].pb(i);
        }
    }
    vector<int> B(n);
    rep(i, 0, n - 1) cin >> B[i];
    int ans = 0;
    rep(i, 0, n - 1) {
        int b = B[i];
        for (int d : adj[b]) {
            if (--cnt[d] == 0) ans++;
        }
        print(ans);
    }
}
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