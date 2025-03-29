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
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    sort(a + 1, a + 1 + n);
    int ans = 0, su = 0;
    rep(i, 1, n - 1) if (a[i + 1] > a[i]) su += a[i + 1] - a[i] - 1;

    if (a[1] > 0&&a[1]!=a[n]) {
        print(-1);
        return;
    }
    if (a[n]!=a[1])
        cout << su + 1 << endl;
    else
        print(0);
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