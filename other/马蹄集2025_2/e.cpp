#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define pb emplace_back
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 2e6 + 6, inf = 1e18, mod = 1e9 + 7;
int ti = 1;
int a[N];
int n, m;
vi e[N];
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) (ans *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return ans;
}
int inv(int x) {
    int p = mod;
    return qpow(x, p - 2, p);
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    sort(a + 1, a + 1 + n);
    int ans = 0;
    rem(i, n, 1) { ans += (m * inv(min(a[i], m))),ans%=mod; }
    cout << ans << endl;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}