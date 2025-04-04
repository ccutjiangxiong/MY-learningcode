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
int n;
void work() {
    cin >> n;
    int ans = 0;
    int a[200] = {3, 1, 2, 1, 0, 1};
    rep(i, 1, n) {
        // print(a[0], a[1], a[2], a[5]);
        int x;
        cin >> x;
        if (a[x]) a[x]--;
        if (a[0] + a[1] + a[2] + a[5] + a[3] == 0 && !ans) ans = i;
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