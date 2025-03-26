#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 1e7 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int n;
void work() {
    cin >> n;
    int ans = 0;
    rep(i, 1, cnt) {
        ans += n / pri[i];
        if (pri[i] > n) break;
    }
    cout << ans << "\n";
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