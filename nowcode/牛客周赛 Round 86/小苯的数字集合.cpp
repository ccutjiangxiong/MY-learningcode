#include <bits/stdc++.h>

#include <numeric>

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
int x, y;

void work() {
    cin >> x >> y;
    int a = x & y;
    int b = x | y;
    int c = x ^ y;
    int d = __gcd(x, y);
    int ans = 3;
    for (auto u : {a, b, c, d}) {
        if (u == 0) ans = min(ans, 1ll);
        for (auto v : {x, y})
            if ((u ^ v) == 0 || (u & v) == 0) ans = min(2ll, ans);
    }
    cout << ans << endl;
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