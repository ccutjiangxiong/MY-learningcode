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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];


 int lft[N], Rmin[N], ll[N];

void work() {
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        lft[i] = 0;
        b[i] = 0;
    }
    {
        map<int, int> mp;
        rep(i, 1, n) {
            if (mp.contains(a[i])) lft[i] = mp[a[i]];
            mp[a[i]] = i;
        }
    }
    {
        map<int, int> mp;
        Rmin[n + 1] = n + 1;
        rem(i, n, 1) {
            b[i] = mp.contains(a[i]) ? mp[a[i]] : n + 1;
            mp[a[i]] = i;
            Rmin[i] = min(b[i], Rmin[i + 1]);
        }
    }
    ll[0] = 0;
    rep(i, 1, n) ll[i] = max(ll[i - 1], lft[i]);
    int M = 1;
    while (M < n + 2) M <<= 1;
    vector<int> seg(2 * M, LLONG_MAX);
    rep(i, 1, n) seg[M + i - 1] = a[i] * (n - i + 1);
    for (int i = M - 1; i >= 1; --i) seg[i] = min(seg[2 * i], seg[2 * i + 1]);

    auto query = [&](int L, int R) {
        int res = LLONG_MAX;
        int l0 = L + M - 1, r0 = R + M - 1;
        while (l0 <= r0) {
            if (l0 & 1) res = min(res, seg[l0++]);
            if (!(r0 & 1)) res = min(res, seg[r0--]);
            l0 >>= 1;
            r0 >>= 1;
        }
        return res;
    };

    ans = inf;
    if (ll[n] == 0) ans = 0;
    rep(i, 1, n) {
        if (Rmin[i + 1] > n) ans = min(ans, a[i] * i);
    }
    rep(i, 1, n) {
        if (ll[i - 1] == 0) ans = min(ans, a[i] * (n - i + 1));
    }

    rep(i, 1, n - 1) {
        int hi = min(Rmin[i + 1], n);
        if (hi >= i + 1) {
            int best2 = query(i + 1, hi);
            ans = min(ans, a[i] * i + best2);
        }
    }

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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];

int lft[N], Rmin[N], ll[N];

void work() {
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        lft[i] = 0;
        b[i] = 0;
    }
    {
        map<int, int> mp;
        rep(i, 1, n) {
            if (mp.contains(a[i])) lft[i] = mp[a[i]];
            mp[a[i]] = i;
        }
    }
    {
        map<int, int> mp;
        Rmin[n + 1] = n + 1;
        rem(i, n, 1) {
            b[i] = mp.contains(a[i]) ? mp[a[i]] : n + 1;
            mp[a[i]] = i;
            Rmin[i] = min(b[i], Rmin[i + 1]);
        }
    }
    ll[0] = 0;
    rep(i, 1, n) ll[i] = max(ll[i - 1], lft[i]);
    int M = 1;
    while (M < n + 2) M <<= 1;
    vector<int> seg(2 * M, LLONG_MAX);
    rep(i, 1, n) seg[M + i - 1] = a[i] * (n - i + 1);
    for (int i = M - 1; i >= 1; --i) seg[i] = min(seg[2 * i], seg[2 * i + 1]);

    auto query = [&](int L, int R) {
        int res = LLONG_MAX;
        int l0 = L + M - 1, r0 = R + M - 1;
        while (l0 <= r0) {
            if (l0 & 1) res = min(res, seg[l0++]);
            if (!(r0 & 1)) res = min(res, seg[r0--]);
            l0 >>= 1;
            r0 >>= 1;
        }
        return res;
    };

    ans = inf;
    if (ll[n] == 0) ans = 0;
    rep(i, 1, n) {
        if (Rmin[i + 1] > n) ans = min(ans, a[i] * i);
    }
    rep(i, 1, n) {
        if (ll[i - 1] == 0) ans = min(ans, a[i] * (n - i + 1));
    }

    rep(i, 1, n - 1) {
        int hi = min(Rmin[i + 1], n);
        if (hi >= i + 1) {
            int best2 = query(i + 1, hi);
            ans = min(ans, a[i] * i + best2);
        }
    }

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