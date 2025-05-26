#include <bits/stdc++.h>
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

int ti = 1;

void work() {
    int H, W, N;
    cin >> H >> W >> N;
    vector<int> X(N), Y(N);
    vector<vector<int>> rowList(H + 1), colList(W + 1);
    rep(i, 0, N - 1) {
        cin >> X[i] >> Y[i];
        rowList[X[i]].pb(i);
        colList[Y[i]].pb(i);
    }
    vector<int> rowCount(H + 1), colCount(W + 1);
    for (int r = 1; r <= H; r++) rowCount[r] = sz(rowList[r]);
    for (int c = 1; c <= W; c++) colCount[c] = sz(colList[c]);
    vector<char> removed(N, false);
    int Q;
    cin >> Q;
    while (Q--) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            int ans = rowCount[v];
            print(ans);
            if (ans > 0) {
                for (int id : rowList[v]) {
                    if (!removed[id]) {
                        removed[id] = 1;
                        colCount[Y[id]]--;
                    }
                }
                rowCount[v] = 0;
            }
        } else {
            int ans = colCount[v];
            print(ans);
            if (ans > 0) {
                for (int id : colList[v]) {
                    if (!removed[id]) {
                        removed[id] = 1;
                        rowCount[X[id]]--;
                    }
                }
                colCount[v] = 0;
            }
        }
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