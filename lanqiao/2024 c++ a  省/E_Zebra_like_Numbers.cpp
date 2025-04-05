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
int ti;
int l, r, x;
int f[N];
map<piii, int> mp;
map<pii, int> mp2;
int rev(int x, int r, int c) {
    if (x <= 0 || r <= 0) return 0;
    if (c * 4 >= r && mp2[{x, r}]) return mp2[{x, r}];
    if (mp.find({x, r, c}) != mp.end()) return mp[{x, r, c}];
    print(x, r, c);
    int ans = 0;
    int k = 0;
    while (f[k + 1] <= x) k++;
    rep(i, 0, 3) {
        int a = (f[k] - 1) / 4;
        if (x >= (i + 1) * f[k]) {
            int g = 0;
            if (r >= i + 1 && (r - i - 1) % 4 == 0 && ((r - i - 1) / 4 <= c + a * i)) g = 1;
            ans += rev(f[k] - 1, r - i, c + a * i) + g;
        } else {
            ans += rev(x - i * f[k], r - i, c + a * i);
            break;
        };
    }
    mp[{x, r, c}] = ans;
    if (c * 4 >= r) mp2[{x, r}] = ans;
    return ans;
}
void work() {
    cin >> l >> r >> x;
    rep(i, 1, 32) f[i] = f[i - 1] + pow(4, i - 1);
    f[33] = inf;
    cout << rev(r, x, 0) - rev(l - 1, x, 0) << endl;
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