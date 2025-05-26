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

int ti, n, k;
void work() {
    int ans = 0;
    cin >> n >> k;
    map<int, int> mp;
    vi a(n + 2);
    rep(i, 1, n) cin >> a[i], mp[a[i]]++;
    sort(a.begin() + 1, a.begin() + 1 + n);
    set<int> s;
    int la = 0;
    rep(i, 1, n) {
        if (a[i] == a[i - 1]) continue;
        int x = a[i];
        int a = i - 1, b = mp[x], c = n - i - mp[x] + 1;
        if (abs(c - a) <= b + k) ans += 1;
        if (abs(i - 1 - (n - i + 1)) <= k) ans += x - la - 1;
        la = x;
    }
    if (k >= n) ans = 1e9;
    print(ans);
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