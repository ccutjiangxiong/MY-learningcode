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
const int N = 2e6 + 5, mod = 998244353, inf = 1e18 + 3;
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

int ti;
int n;
int isp[N], pri[N], Phi[N], cnt = 0;
void euler(int n) {
    Phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i, Phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
            Phi[i * pri[j]] = Phi[i] * (pri[j] - (i % pri[j] != 0));
            if (i % pri[j] == 0) break;
        }
    }
}
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}
// p为质数
int invp(int a, int p) { return qpow(a, p - 2, p); }
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) return a + (x = 1) + (y = 0) - 1;
    int x1, y1;
    int gcd = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return gcd;
}
int invp2(int a, int p) {
    int x = 0, y = 0;
    return exgcd(a, p, x, y) == 1 ? (x % p + p) % p : -1;
}
void work() {
    cin >> n;
    int ans = 1, b = 0;
    for (int x = 1; pri[x] <= n; x++) {
        int k = pri[x], u = 1;
        int res = 0;
        while (n - k >= 0) {
            res += u * (n - k + 1), k += pri[x], u = 0;
            int q = k;
            while (q % pri[x] == 0) q /= pri[x], u++;
        }
        if (x == 1)
            b += res;
        else
            ans += res;
    }
    cout << ans * invp(ans + b, mod) << ' ';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<int> ns(T), res(T);
    for (int i = 0; i < T; i++) {
        cin >> ns[i];
    }

    for (int i = 0; i < T; i++) {
        int n = ns[i];
        int e2 = 0;
        for (int p = 2; p <= n; p <<= 1) {
            e2 += n / p;
        }
        int denom = (e2 + 1) % mod;
        res[i] = qpow(denom, mod - 2, mod);
    }

    for (int i = 0; i < T; i++) {
        cout << res[i] << (i + 1 < T ? ' ' : '\n');
    }
    return 0;
}