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

int ti, q,n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];
string s;

inline int rotL(int mask, int d) {
    return ((mask << d) | (mask >> (26 - d))) & ((1 << 26) - 1);
}

struct Node {
    int l, r, mask, tag;
} tr[N * 4];

void build(int p, int L, int R) {
    tr[p].l = L;
    tr[p].r = R;
    tr[p].tag = 0;
    if (L == R) {
        tr[p].mask = 1 << (s[L - 1] - 'a');
        return;
    }
    int M = (L + R) >> 1;
    build(p << 1, L, M);
    build(p << 1 | 1, M + 1, R);
    tr[p].mask = tr[p << 1].mask ^ tr[p << 1 | 1].mask;
}


void apply_rot(int p, int d) {
    tr[p].mask = rotL(tr[p].mask, d);
    tr[p].tag = (tr[p].tag + d) % 26;
}

void pushdown(int p) {
    if (tr[p].tag) {
        apply_rot(p << 1, tr[p].tag);
        apply_rot(p << 1 | 1, tr[p].tag);
        tr[p].tag = 0;
    }
}
void update_rot(int p, int x, int y, int d) {
    if (x <= tr[p].l && tr[p].r <= y) {
        apply_rot(p, d);
        return;
    }
    pushdown(p);
    int M = (tr[p].l + tr[p].r) >> 1;
    if (x <= M) update_rot(p << 1, x, y, d);
    if (y > M) update_rot(p << 1 | 1, x, y, d);
    tr[p].mask = tr[p << 1].mask ^ tr[p << 1 | 1].mask;
}
int query_mask(int p, int x, int y) {
    if (x <= tr[p].l && tr[p].r <= y) return tr[p].mask;
    pushdown(p);
    int res = 0;
    int M = (tr[p].l + tr[p].r) >> 1;
    if (x <= M) res ^= query_mask(p << 1, x, y);
    if (y > M) res ^= query_mask(p << 1 | 1, x, y);
    return res;
}

void work() {
    cin >> n >> q;
    cin >> s;
    build(1, 1, n);
    while (q--) {
        int o, l, r, d;
        cin >> o >> l >> r;
        if (o == 1) {
            cin >> d;
            d %= 26;  
            update_rot(1, l, r, d);
        } else {
            int mask = query_mask(1, l, r);
            if (__builtin_popcount(mask) <= 1)
                pt("Yes");
            else
                pt("No");
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