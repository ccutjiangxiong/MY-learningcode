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
using ll = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll l, r;
    cin >> l >> r;

    const string pattern = "4931";
    int m = pattern.size();

    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m;) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }

    vector<vector<int>> nxt(m + 1, vector<int>(10));
    for (int st = 0; st <= m; st++) {
        for (int d = 0; d < 10; d++) {
            if (st == m) {
                nxt[st][d] = m;
            } else {
                int len = st;
                while (len > 0 && pattern[len] - '0' != d) len = lps[len - 1];
                if (pattern[len] - '0' == d) len++;
                nxt[st][d] = len;
            }
        }
    }

    function<__int128(ll)> solve = [&](ll x) {
        if (x < 0) return (__int128)0;
        vector<int> digs;
        while (x > 0) {
            digs.push_back(x % 10);
            x /= 10;
        }
        if (digs.empty()) digs.push_back(0);
        reverse(digs.begin(), digs.end());
        int n = digs.size();

        static pair<ll, __int128> dp[20][5][2];
        static bool vis[20][5][2];
        memset(vis, 0, sizeof(vis));

        function<pair<ll, __int128>(int, int, int)> dfs = [&](int pos, int st, int tight) {
            if (pos == n) {
                return make_pair(st == m ? 1LL : 0LL, (__int128)0);
            }
            if (!tight && vis[pos][st][tight]) {
                return dp[pos][st][tight];
            }
            ll cnt = 0;
            __int128 sum = 0;
            int up = tight ? digs[pos] : 9;
            __int128 place = 1;
            for (int i = pos + 1; i < n; i++) place *= 10;

            for (int d = 0; d <= up; d++) {
                int nst = nxt[st][d];
                int nt = tight && (d == up);
                auto [c, s] = dfs(pos + 1, nst, nt);
                cnt += c;
                sum += s + (__int128)d * place * c;
            }
            if (!tight) {
                vis[pos][st][tight] = true;
                dp[pos][st][tight] = {cnt, sum};
            }
            return make_pair(cnt, sum);
        };

        return dfs(0, 0, 1).second;
    };

    __int128 ans = solve(r) - solve(l - 1);
    cout << (long long)ans << "\n";
    return 0;
}