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
const int N = 2e6 + 5, mod = 20091119, inf = 1e18 + 3;
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
// ...existing code...

// const int mod = 20091119;

// 删除原有的 f[], pre(), dfs()

void work() {
    string s;
    cin >> s;
    int L = s.size();
    // 预处理 10 的幂
    vector<int> p10(L + 1);
    p10[0] = 1;
    for (int i = 1; i <= L; i++) {
        p10[i] = (int64_t)p10[i - 1] * 10 % mod;
    }
    // 统计长度小于 L 的所有回文数
    int ans = 0;
    for (int len = 1; len < L; len++) {
        int half = (len + 1) / 2;
        ans = (ans + 9LL * p10[half - 1]) % mod;
    }
    // 统计与 n 同长度且 <= n 的回文数
    int half = (L + 1) / 2;
    int prefix = 0;
    for (int i = 0; i < half; i++) {
        prefix = (int64_t(prefix) * 10 + (s[i] - '0')) % mod;
    }
    int base = p10[half - 1];  // 最小同位数回文的前缀
    int cnt = (prefix - base + mod) % mod;
    // 构造由 prefix 生成的回文并比较
    string t = s.substr(0, half);
    string r = t;
    if (L & 1) r.pop_back();
    reverse(r.begin(), r.end());
    if (t + r <= s) cnt = (cnt + 1) % mod;
    ans = (ans + cnt) % mod;
    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ti = 1;
    // ti 只读一次
    // if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}