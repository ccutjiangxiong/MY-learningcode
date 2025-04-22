#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;
using namespace numbers;
void be(int u, int v, auto e[N]) {
    cin >> u >> v;
    e[u].pb(v), e[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;

int n, k;
int dp[N], pre[N], a[N];

void work() {
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i], pre[i] = pre[i - 1] + a[i];
    multiset<int> fd;
    fd.insert(0);
    fd.insert(dp[0] - pre[1]);
    
    rep(i, 1, n) {
        int tmp = *fd.rbegin();
        dp[i] = pre[i] + tmp;
        if (i == n) break;
        fd.insert(dp[i] - pre[i + 1]);
        int j = i - k;
        if (j >= 0) {
            int x = (j == 0) ? 0 : dp[j - 1] - pre[j];
            auto itr = fd.find(x);
            if (itr != fd.end()) fd.erase(itr);
        }
    }
    cout << dp[n];
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