#include <bits/stdc++.h>
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
int ti = 1;
int n;
int a[N];
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int x = 0;
    int ans = 0, l = 1;
    rep(i, 1, n) {
        if (i == l) continue;
        if (gcd(a[i], a[l]) != 1) l = i + 1, ans++;
    }
    if (ans)
        cout << ans << endl;
    else
        cout << -1 << endl;
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