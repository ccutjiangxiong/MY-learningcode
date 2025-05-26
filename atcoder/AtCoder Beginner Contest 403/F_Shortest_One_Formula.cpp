#include <bits/stdc++.h>

#include <memory>
#include <string>

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
using ull = uint64_t;

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
map<int, string> mp;
void work() {
    int n;
    cin >> n;
    mp[1] = "1";
    mp[2] = "1+1";
    for (int x = 1; x <= 2000; x = x * 10 + 1)
        for (int y = 1; y <= 2000; y = y * 10 + 1) {
            string t1, t2;
            if (x * y <= n) t1 = '(' + to_string(x) + ')' + '*' + '(' + to_string(y) + ')';
            if (x + y <= n) t2 = t1 = to_string(x) + '+' + to_string(y);
        }

    rep(i, 1, n) {
        string s = "1";
        rep(i, 2, n) s += "+1";
        mp[i] = s;
        rep(j, 1, i) rep(k, 1, i) { if () }
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