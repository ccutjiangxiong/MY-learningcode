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
int n, k;
int a[N];

void work() {
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i];
    sort(a + 1, a + 1 + n, [](int x, int y) { return x > y; });
    int ans = 0;
    int sum = 0, mi = 0;
    rep(i, 1, n)

        if (++sum * a[i] >= k) ans++,
        sum = 0;

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