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
#define ll long long
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e2 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = unsigned long long;
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

int t;
ll max_factor, n;
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)ans * a % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}
inline bool mr(int n) {
    if (n < 3 || n % 2 == 0) {
        return n == 2;
    }
    int u = n - 1, t = 0;
    while (u % 2 == 0) {
        u /= 2, t++;
    }
    int ud[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (int a : ud) {
        int v = qpow(a, u, n);
        if (v == 1 || v == 0 || v == n - 1) continue;
        for (int i = 1; i <= t; i++) {
            v = (ill)v * v % n;
            if (v == n - 1 && i != t) {
                v = 1;
                break;
            }
            if (v == 1) return 0;
        }
        if (v != 1) return 0;
    }
    return 1;
}
int pr(int x) {
    int t = 0;
    int c = ran(1, x - 1);
    int s = t;
    int step = 0, goal = 1;
    int val = 1;
    for (goal = 1;; goal <<= 1, s = t, val = 1) {
        for (step = 1; step <= goal; ++step) {
            t = ((ill)t * t % x + c) % x;
            val = (ill)val * abs(t - s) % x;
            // 如果 val 为 0，退出重新分解
            if (!val) return x;
            if (step % 127 == 0) {
                int d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        int d = gcd(val, x);
        if (d > 1) return d;
    }
}
void fac(ll x) {
    if (x <= max_factor || x < 2) return;
    if (mr(x)) {                          // 如果x为质数
        max_factor = max(max_factor, x);  // 更新答案
        return;
    }
    ll p = x;
    while (p >= x) p = pr(x);  // 使用该算法
    while ((x % p) == 0) x /= p;
    fac(x), fac(p);  // 继续向下分解x和p
}

signed main() {
    cin >> t;
    while (t--) {
        srand((unsigned)time(NULL));
        max_factor = 0;
        cin >> n;
        fac(n);
        if (max_factor == n)  // 最大的质因数即自己
            cout << "Prime\n";
        else
            cout << max_factor << '\n';
    }
    return 0;
}