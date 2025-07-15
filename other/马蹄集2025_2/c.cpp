#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define pb emplace_back
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 2e6 + 6, inf = 1e18, mod = 1e9 + 7;
int ti = 1;
int a[N];
int n;
vi e[N];
void work() {
    cin >> n;
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}