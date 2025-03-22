#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5,mod = 1e9 + 7, inf = 1e18 + 3;
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
int n, k;
string solve(int x, int q) {
    if (x == 1) return to_string(q) + ' ';
    int k = 1;
    while (k * 2 < x) k <<= 1;
    string t = solve(x - k, q);
    string s;
    s += t;
    rep(i, 1, 2 * k - x) s += "0 ";
    s += t;
    return s;
}
void work() {
    cin >> n >> k;
    cout << solve(n, k) << endl;
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