#include <complex>
#include <iostream>

#define INF 0x3f3f3f3f
#define lc u << 1
#define rc u << 1 | 1

using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 ill;
typedef complex<double> cpx;
int mod = 19260817;
char buf[1 << 22], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin);
    return *(p1++);
}
inline ll rd() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        x %= mod;
        ch = getchar();
    }
    return x * f;
}
inline void wt(ill x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        wt(x / 10);
    }
    putchar(x % 10 + '0');
}
const int N = 1e7 + 5;
ll n, isp[N], prime[N], cnt = 0, phi[N];
ll pre[N];
void euler(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!phi[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && prime[j] * i <= n; j++) {
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (phi[prime[j]]);
        }
    }
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + phi[i];
}

int main() {
    int t, m;
    cin >> t;

    euler(1e7);
    while (t--) {
        cin >> n >> m;
        ll ans = 0;
        for (int i = 1; i <= cnt && prime[i] <= m; i++) {
            int x = n / prime[i];
            ans += pre[x] * 2 - 1;
        }
        cout << ans << endl;
    }
}