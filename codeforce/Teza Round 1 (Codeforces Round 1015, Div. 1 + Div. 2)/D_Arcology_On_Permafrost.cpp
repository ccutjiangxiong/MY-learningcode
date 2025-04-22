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
int n, m, k;
int ans[N];
void work() {
    cin >> n >> m >> k;
    rep(i, 1, n) ans[i] = 0;
    // int x = max(k, n / (m + 1));
    // rep(i, 1, n) cout << i % x << ' ';
    int u = (n < (m + 1) * k ? k : n / (m + 1));
    // print(u, x);
    rep(i,0 , n-1) cout << i % u << ' ';
    cout << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}