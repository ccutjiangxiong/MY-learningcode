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
const int N = 1e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti=1 ,n,m,k,a[N],b[N],c[N],ans,res,x,y,z;
vi e[N];


int brm[N];  
int cnt = 1;
int cnt2;
int up[N][22], dv[N];
int rv[N], rm[N];

struct PST {
    int lc, rc, v;
} trv[(100000 * 20)], trm[(100000 * 20)];
int totv = 0, totm = 0;


int build_val(int l, int r) {
    int p = ++totv;
    if (l == r) {
        trv[p].v = ::a[l];
    } else {
        int m = (l + r) >> 1;
        trv[p].lc = build_val(l, m);
        trv[p].rc = build_val(m + 1, r);
    }
    return p;
}

int build_mod(int l, int r) {
    int p = ++totm;
    if (l < r) {
        int m = (l + r) >> 1;
        trm[p].lc = build_mod(l, m);
        trm[p].rc = build_mod(m + 1, r);
    }
    return p;
}

int update_val(int prev, int l, int r, int pos, int x) {
    int p = ++totv;
    trv[p] = trv[prev];
    if (l == r) {
        trv[p].v = x;
    } else {
        int m = (l + r) >> 1;
        if (pos <= m)
            trv[p].lc = update_val(trv[prev].lc, l, m, pos, x);
        else
            trv[p].rc = update_val(trv[prev].rc, m + 1, r, pos, x);
    }
    return p;
}
int query_val(int p, int l, int r, int pos) {
    if (l == r) return trv[p].v;
    int m = (l + r) >> 1;
    if (pos <= m)
        return query_val(trv[p].lc, l, m, pos);
        return query_val(trv[p].rc, m + 1, r, pos);
}

int update_mod(int prev, int l, int r, int pos, int ver) {
    int p = ++totm;
    trm[p] = trm[prev];
    if (l == r) {
        trm[p].v = ver;
    } else {
        int m = (l + r) >> 1;
        if (pos <= m)
            trm[p].lc = update_mod(trm[prev].lc, l, m, pos, ver);
        else
            trm[p].rc = update_mod(trm[prev].rc, m + 1, r, pos, ver);
    }
    return p;
}
int query_mod(int p, int l, int r, int pos) {
    if (l == r) return trm[p].v;
    int m = (l + r) >> 1;
    if (pos <= m)
        return query_mod(trm[p].lc, l, m, pos);
        return query_mod(trm[p].rc, m + 1, r, pos);
}

int lca(int u, int v) {
    if (dv[u] < dv[v]) std::swap(u, v);
    int diff = dv[u] - dv[v];
    for (int i = 0; i < 22; i++)
        if (diff >> i & 1) u = up[u][i];
    if (u == v) return u;
    for (int i = 22 - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    cnt2 = 1;
    cnt2 = 1;
    cnt = 1;
    memset(brm, 0, sizeof brm);
    brm[1] = 1;
    dv[1] = 0;
    up[1][0] = 0;
    rep(j, 1, 22 - 1) up[1][j] = 0;
    totv = totm = 0;
    rv[1] = build_val(1, n);
    rm[1] = build_mod(1, n);

    string op;
    while (m--) {
        cin >> op;
        if (op == "upd") {
            int x, y;
            cin >> x >> y;
            int old = brm[cnt];
            int nv = ++cnt2;
            rv[nv] = update_val(rv[old], 1, n, x, y);
            rm[nv] = update_mod(rm[old], 1, n, x, nv);
            dv[nv] = dv[old] + 1;
            up[nv][0] = old;
            rep(j, 1, 22 - 1) up[nv][j] = up[up[nv][j - 1]][j - 1];
            brm[cnt] = nv;
        } else if (op == "branch") {
            int b;
            cin >> b;
            if (!brm[b]) brm[b] = brm[cnt];
            cnt = b;
        } else if (op == "query") {
            int b, k;
            cin >> b >> k;
            int v = brm[b];
            cout << query_val(rv[v], 1, n, k) << "\n";
        } else if (op == "check") {
            int x, y, k;
            cin >> x >> y >> k;
            int vx = brm[x], vy = brm[y];
            int w = lca(vx, vy);
            int t0 = query_mod(rm[w], 1, n, k);
            int t1 = query_mod(rm[vx], 1, n, k);
            int t2 = query_mod(rm[vy], 1, n, k);
            if (t1 > t0 && t2 > t0)
                cout << "NO\n";
            else
                cout << "YES\n";
        }
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