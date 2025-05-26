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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;
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

void work() {
    int n;
    cin >> n;
    if (n % 2 == 1) {
        print(-1);
        return;
    }
    int p_found = 0;
    rep(i, 1, cnt) {
        int p = pri[i];
        if (p > n) break;
        if (p == 2) continue;
        if (n % p != 0 && n - p > 1 && !isp[n - p]) {
            p_found = p;
            break;
        }
    }
    if (!p_found) {
        print(-1);
        return;
    }
    vector<int> a(n);
    a[0] = 1;
    for (int i = 1; i < n; i++) {
        a[i] = (a[i - 1] + p_found - 1) % n + 1;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    euler(N - 1);
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}