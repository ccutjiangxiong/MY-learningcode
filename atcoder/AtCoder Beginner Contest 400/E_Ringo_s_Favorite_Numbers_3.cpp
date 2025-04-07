#include <bits/stdc++.h>

#include <algorithm>

#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
int isp[N], pri[N], cnt = 0;
void euler(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
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
int n;
vector<int> ans;
void work() {
    cin >> n;
    int x = upper_bound(ans.begin(), ans.end(), n) - ans.begin();
    print(ans[x - 1]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    euler(1e6 + 5);
     for (int i = 1; i <= cnt; i++) {
        int pi2 = pri[i] * pri[i];
        for (int val_i = pi2; val_i <= 1e12; val_i *= pi2) {
            for (int j = i + 1; j <= cnt; j++) {
                int pj2 = pri[j] * pri[j];
                if (val_i * pj2 > 1e12) break;

                for (int val_j = pj2; val_i * val_j <= 1e12; val_j *= pj2) {
                    ans.push_back(val_i * val_j);  
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    // for (int x : ans) print(x);
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}