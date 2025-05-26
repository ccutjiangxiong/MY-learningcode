#include <bits/stdc++.h>

#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a);
#define cnt1(a) __builtin_popcount(a);
#define cnt0(a) __builtin_clz(a);
#define odd1(a) __builtin_parity(a);
#define all(a) a.begin(), a.end()
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
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, p[N];
set<int> s1, s2;
void work() {
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    if (n < 4) {
        print(0);
        return;
    }
    int M = n - 1;
    vector<int> D(M);
    for (int i = 0; i < M; i++) D[i] = (p[i + 1] > p[i] ? 1 : -1);
    vector<int> peak(M, 0), valley(M, 0);
    for (int i = 1; i < M; i++) {
        if (D[i - 1] == 1 && D[i] == -1) peak[i] = 1;
        if (D[i - 1] == -1 && D[i] == 1) valley[i] = 1;
    }
    const int INF = M;
    vector<int> adfjalsdjlassdjalsk(M + 1, INF), nextValley(M + 1, INF);
    for (int i = M - 1; i >= 0; i--) {
        adfjalsdjlassdjalsk[i] = peak[i] ? i : adfjalsdjlassdjalsk[i + 1];
        nextValley[i] = valley[i] ? i : nextValley[i + 1];
    }
    int ans = 0;
    for (int L = 0; L < M; L++) {
        if (D[L] != 1) continue;  
        if (M - L < 3) break;     
        int p1 = adfjalsdjlassdjalsk[L + 1];
        int v1 = nextValley[L + 1];
        if (p1 >= M || v1 >= M) continue;  
        int rmin = max(p1, v1);
        int p2 = (p1 + 1 < M ? adfjalsdjlassdjalsk[p1 + 1] : INF);
        int v2 = (v1 + 1 < M ? nextValley[v1 + 1] : INF);
        int rlim = min(p2, v2) - 1;  
        int low = max(rmin, L + 2); 
        int high = min(rlim, M - 1);
        if (high >= low) ans += (high - low + 1);
    }
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