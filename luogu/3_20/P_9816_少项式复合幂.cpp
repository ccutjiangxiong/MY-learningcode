#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 1e5 + 10, M = 25;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int m, q;
int mod_val, f[N][M], a[N], b[N];

int qpow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = x * x % mod_val) {
        if (y & 1) res = res * x % mod_val;
    }
    return res;
}

void work() {
    cin >> m >> q >> mod_val;
    rep(i, 1, m) cin >> a[i] >> b[i];
    rep(i, 0, mod_val - 1) {
        rep(j, 1, m) { f[i][0] = (f[i][0] + a[j] * qpow(i, b[j]) % mod_val) % mod_val; }
    }
    rep(j, 1, M - 1) {
        rep(i, 0, mod_val - 1) { f[i][j] = f[f[i][j - 1]][j - 1]; }
    }
    rep(i, 1, q) {
        int x, y, ans, cnt = 0;
        cin >> x >> y;
        ans = x % mod_val;
        while (y) {
            if (y & 1) ans = f[ans][cnt];
            cnt++;
            y >>= 1;
        }
        cout << ans << endl;
    }
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