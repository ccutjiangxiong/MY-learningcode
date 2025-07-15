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

int ti;
int n;
int p[N];
void work() {
    cin >> n;
    set<int> ss;
    rep(i, 1, 2 * n) ss.insert(i);
    rep(i, 1, n) rep(j, 1, n) {
        int x;
        cin >> x;
        p[i + j] = x;
        ss.erase(x);
    }
    p[1] = *ss.begin();
    rep(i, 1, 2 * n) cout << p[i] << " \n"[i == 2 * n];
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