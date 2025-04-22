#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

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

int ti = 1;
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
int fplus(int a, int b, int mod) {
    int ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ans;
}
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = a * ans % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
// p为质数
int invp(int a, int p) { return qpow(a, p - 2, p); }
int exgcd(int a, int b, int& x, int& y) {
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

void fwt(vector<int>& a, int n, bool inv) {
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; ++j) {
                int u = a[i + j], v = a[i + j + len];
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len] = u - v >= 0 ? u - v : u - v + mod;
            }
        }
    }
    if (inv) {
        int inv_n = qpow(n, mod - 2, mod);
        for (int& x : a) x = x * inv_n % mod;
    }
}
int n;
void Or(int a[], int type, int p) {
    for (int x = 2; x <= n; x <<= 1) {
        int k = x >> 1;
        for (int i = 0; i < n; i += x)
            for (int j = 0; j < k; j++) (a[i + j + k] += a[i + j] * type) %= p;
    }
}
void And(int a[], int type, int p) {
    for (int x = 2; x <= n; x <<= 1) {
        int k = x >> 1;
        for (int i = 0; i < n; i += x) {
            for (int j = 0; j < k; j++) (a[i + j] += a[i + j + k] * type) %= p;
        }
    }
}
void Xor(int a[], int type, int p) {
    for (int x = 2; x <= n; x <<= 1) {
        int k = x >> 1;
        for (int i = 0; i < n; i += x)
            for (int j = 0; j < k; j++) {
                (a[i + j] += a[i + j + k]) %= p;
                (a[i + j + k] = a[i + j] - a[i + j + k] * 2) %= p;
                (a[i + j] *= type) %= p;
                (a[i + j + k] *= type) %= p;
            }
    }
}
void work() {
    int N;
    cin >> N;
    vector<int> A(N);
    int V = 0;
    vector<char> seen(3005, 0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        V = max(V, A[i]);
    }
    for (int x : A) {
        if (seen[x]) {
            print(0);
            return;
        }
        seen[x] = 1;
    }
    int M = 1;
    while (M <= V) M <<= 1;
    vector<int> f(M, 0);
    for (int x : A) f[x] = 1;
    fwt(f, M, false);
    for (int i = 0; i < M; i++) f[i] = f[i] * f[i] % mod;
    fwt(f, M, true);
    int ans = 1;
    for (int z = 1; z < M; z++) {
        int cnt2 = f[z];
        if (cnt2) {
            int e = cnt2 / 2;
            ans = ans * qpow(z, e % (mod - 1), mod) % mod;
        }
    }
    print(ans);
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