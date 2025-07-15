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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
vi e[N];

int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }

void work() {
    cin >> n >> m;
    rep(len, 1, n) {
        int l = n - len + 1;
        rep(mask, 1, (1 << l) - 1) {
            rep(i, 1, len) fa[i] = i;
            rep(i, 1, n) c[i] = 0;
            rep(j, 1, l) if (mask >> (j - 1) & 1) {
                rep(k, 1, len) {
                    int p = j + k - 1;
                    if (c[p])
                        uni(c[p], k);
                    else
                        c[p] = k;
                }
            }
            int fc = 0;
            rep(i, 1, len) if (find(i) == i) fc++;
            rep(i, 1, n) if (!c[i]) fc++;
            (ans += qpow(m, fc, mod) * (odd1(mask) ? 1 : -1) + mod) %= mod;
        }
    }
    tot = qpow(m, n, mod);
    (ans *= qpow(tot, mod - 2, mod)) %= mod;
    pt(ans);
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