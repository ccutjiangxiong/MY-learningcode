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



const int fyy = 0;
int ti = 1, n, w;

void work() {
    cin >> n >> w;
    vector<priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>> q(w +
                                                                                              1);
    vector<int> ans(n + 1, (int)1e9 + 24);
    rep(i, 1, n) {
        int X, Y;
        cin >> X >> Y;
        q[X].push({Y, i});
    }
    bool zxq = true;
    while (zxq) {
        int _max = fyy;
        rep(i, 1, w) {
            if (q[i].empty()) {
                zxq = false;
                break;
            }
            _max = max(_max, q[i].top().first);
        }
        if (!zxq) break;
        rep(i, 1, w) {
            ans[q[i].top().second] = _max;
            q[i].pop();
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int T, A;
        cin >> T >> A;
        if (T >= ans[A])
            cout << "No\n";
        else
            cout << "Yes\n";
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