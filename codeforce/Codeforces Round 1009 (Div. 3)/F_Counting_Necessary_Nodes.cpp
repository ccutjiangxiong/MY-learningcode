#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
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
int ti;
int l1, r1, l2, r2;
int solve(int l1, int r1, int l2, int r2) {
    if (l2 - l1 == 0 || r2 - r1 == 0) return 0;
    if (r2 - r1 == 1 && l2 - l1 == 1) return 1;
    int h = min(r2 - r1, l2 - l1);
    int k = 1 << 30;
    int x, y;
    while (k) {
        if (k <= h) {
            x = l1 / k * k;
            y = r1 / k * k;
            if (x < l1) x += k;
            if (y < r1) y += k;
            if (x + k <= l2 && y + k <= r2) break;
        }
        k >>= 1;
    }
    int a = x, b = y;
    int t1 = 1, t2 = 1;
    t1 = (l2 - a) / k, t2 = (r2 - b) / k;
    while (a + t1 * k > l2) t1--;
    while (b + t2 * k > r2) t2--;
    int ans = t1 * t2;
    ans += solve(l1, r1, a, r2);
    ans += solve(a, r1, a + t1 * k, b);
    ans += solve(a, b + t2 * k, a + t1 * k, r2);
    ans += solve(a + t1 * k, r1, l2, r2);
    return ans;
}
void work() {
    cin >> l1 >> l2 >> r1 >> r2;
    cout << solve(l1, r1, l2, r2) << endl;
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