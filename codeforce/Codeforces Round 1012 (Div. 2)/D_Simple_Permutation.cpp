#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 1e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
int n;
int a[N];
set<int> ss, tt;
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

void work() {
    cin >> n;

    rep(i, 1, n) ss.insert(i);
    vector<int> ans;
    int sum = 0;
    while (ss.size()) {
        if (ans.size() >= n / 3 - 1) break;
        vector<int> to_erase;
        for (int x : ss) {
            while (tt.find((sum + x + ans.size()) / (ans.size() + 1)) != tt.end()) {
                ans.push_back(x);
                to_erase.push_back(x);
                sum += x;
                break;
            }
        }
        if (to_erase.size())
            for (int x : to_erase) ss.erase(x);
    }
    for (int x : ss) ans.push_back(x);
    for (int x : ans) cout << x << ' ';
    cout << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    euler(N);
    rep(i, 1, cnt) tt.insert(pri[i]);
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}