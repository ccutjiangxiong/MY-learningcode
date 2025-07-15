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
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, kans, res, cnt, x, y, z;
int n1, n2, n3;

void work() {
    cin >> n1 >> n2 >> n3;
    vector<pii> A(n1), B(n2), C(n3);
    for (auto& pt : A) cin >> pt.fi >> pt.se;
    for (auto& pt : B) cin >> pt.fi >> pt.se;
    for (auto& pt : C) cin >> pt.fi >> pt.se;

    // 1) 前缀时间
    auto make_prefix = [&](auto& P) {
        int m = P.size();
        vector<ld> T(m, 0);
        for (int i = 1; i < m; i++) {
            ld dx = P[i].fi - P[i - 1].fi;
            ld dy = P[i].se - P[i - 1].se;
            T[i] = T[i - 1] + sqrtl(dx * dx + dy * dy);
        }
        return T;
    };
    auto TA = make_prefix(A);
    auto TB = make_prefix(B);
    auto TC = make_prefix(C);

    // 2) 合并时间节点
    vector<ld> ev;
    ev.reserve(n1 + n2 + n3);
    ev.insert(ev.end(), TA.begin(), TA.end());
    ev.insert(ev.end(), TB.begin(), TB.end());
    ev.insert(ev.end(), TC.begin(), TC.end());
    sort(ev.begin(), ev.end());
    ev.erase(unique(ev.begin(), ev.end()), ev.end());

    ld ans = 0;
    int ia = 0, ib = 0, ic = 0;
    for (int p = 0; p + 1 < (int)ev.size(); p++) {
        ld t0 = ev[p], t1 = ev[p + 1], dt = t1 - t0;
        if (dt <= 0) continue;

        // 3) 找出各自所在段号 ia, ib, ic
        while (ia + 1 < (int)TA.size() && TA[ia + 1] <= t0) ia++;
        while (ib + 1 < (int)TB.size() && TB[ib + 1] <= t0) ib++;
        while (ic + 1 < (int)TC.size() && TC[ic + 1] <= t0) ic++;

        // 4) 计算 t0 时刻的坐标和速度向量
        auto get_state = [&](auto& P, auto& T, int i, ld t) -> pair<pair<ld, ld>, pair<ld, ld>> {
            ld segLen = T[i + 1] - T[i];
            ld ratio = segLen > 0 ? (t - T[i]) / segLen : 0;
            ld x0 = P[i].fi + (P[i + 1].fi - P[i].fi) * ratio;
            ld y0 = P[i].se + (P[i + 1].se - P[i].se) * ratio;
            ld vx = segLen > 0 ? (P[i + 1].fi - P[i].fi) / segLen : 0;
            ld vy = segLen > 0 ? (P[i + 1].se - P[i].se) / segLen : 0;
            return {{x0, y0}, {vx, vy}};
        };

        auto [A0, vA] = get_state(A, TA, ia, t0);
        auto [B0, vB] = get_state(B, TB, ib, t0);
        auto [C0, vC] = get_state(C, TC, ic, t0);

        // D(t) = A(t) - B(t) = D0 + Dv * t  （t∈[0,dt]）
        ld D0x = A0.first - B0.first, D0y = A0.second - B0.second;
        ld Dvx = vA.first - vB.first, Dvy = vA.second - vB.second;
        ld E0x = A0.first - C0.first, E0y = A0.second - C0.second;
        ld Evx = vA.first - vC.first, Evy = vA.second - vC.second;

        // cross(t) = (D0 + Dv t) x (E0 + Ev t) = cc + bb*t + aa*t^2
        ld aa = Dvx * Evy - Dvy * Evx;
        ld bb = D0x * Evy - D0y * Evx + Dvx * E0y - Dvy * E0x;
        ld cc = D0x * E0y - D0y * E0x;

        auto area_at = [&](ld t) { return fabsl(aa * t * t + bb * t + cc) * 0.5L; };

        // … 上文保持不变 …

        // 5) 在 [0,dt] 上取端点和用三分法搜索极大值
        ans = max({ans, area_at(0), area_at(dt)});

        // 三分搜索
        ld l = 0, r = dt;
        for (int it = 0; it < 60; it++) {
            ld m1 = l + (r - l) / 3;
            ld m2 = r - (r - l) / 3;
            ld f1 = area_at(m1);
            ld f2 = area_at(m2);
            if (f1 < f2)
                l = m1;
            else
                r = m2;
        }
        ans = max(ans, area_at((l + r) * 0.5L));

    }

    cout << fixed << setprecision(10) << ans << "\n";
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