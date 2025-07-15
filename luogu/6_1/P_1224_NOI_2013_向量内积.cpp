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
#define int unsigned int
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];
int d;
int gr[N][105];
char buf[1 << 21], *p1 = buf, *p2 = buf;
char gc() {
    if (p1 == p2) {
        size_t bytesRead = fread(buf, 1, 1 << 21, stdin);
        p2 = buf + bytesRead;
        p1 = buf;
        if (bytesRead == 0) return EOF;
    }
    return *p1++;
}
inline int rd() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f *= -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }
    return x * f;
}
inline void wt(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) wt(x / 10);
    putchar(x % 10 + '0');
}
template <typename... T>
void nrd(T&... a) {
    ((a = rd()), ...);
}
template <typename... T>
void nwt(T... a) {
    ((wt(a), putchar(' ')), ...);
    putchar('\n');
}
int find(int x) {
    rep(i, 1, x - 1) {
        int t = c[i];
        int ans = 0;
        rep(j, 1, d)(ans += (gr[t][j] * gr[x][j]));
        // print(x, i, ans);
        if (ans % k == 0) return t;
    }
    return -1;
}
// …existing includes& macros…

void work() {
    n = rd(), d = rd(), k = rd();
    rep(i, 1, n) rep(j, 1, d) gr[i][j] = rd() % k;
    rep(i, 1, n) c[i] = i;
    rep(_, 1, 6) {
        shuffle(c + 1, c + 1 + n, rng);
        // 前缀和只需要 d 维
        rep(j, 1, d) a[j] = 0;
        rep(i, 1, n) {
            int t = c[i];
            if (i != 1) {
                int ans = 0;
                // 计算当前向量 t 与前缀和 a[] 的内积
                rep(j, 1, d) ans += a[j] * gr[t][j];
                if (ans % k != ((t - 1) & 1)) {
                    // 只在不匹配时，扫描前缀中每个向量做一次 O(m) 检验
                    rep(idx, 1, i - 1) {
                        int u = c[idx], tot = 0;
                        rep(j, 1, d) tot += gr[t][j] * gr[u][j];
                        if (tot % k == 0) {
                            print(min(u, t), max(u, t));
                            return;
                        }
                    }
                }
            }
            // 更新前缀和 a[]
            if (k == 2) {
                rep(j, 1, d) a[j] = (a[j] + gr[t][j]) & 1;
            } else {  // k == 3
                rep(j, 1, d) {
                    unsigned v = gr[t][j];
                    a[j] = (a[j] + v * v % k) % k;
                }
            }
        }
    }
    print(-1);
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