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
int a[N], h[N];
int b[N], c[N];

void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    // sort(a + 1, a + 1 + n);
    rep(i, 1, n) h[a[i]]++;
    rep(i, 1, 1e5) if (h[i]) for (int j = i; j <= 1e5; j += i) if (h[j]) {
        if (j == i)
            b[i] += h[i] - 1, c[i] += h[i] - 1;
        else
            b[i] += h[j], c[j] += h[i];
    }
    rep(i, 1, n) print(b[a[i]], c[a[i]]);
    int ans = 0, sum = 0;
    rep(i, 1, n) sum += b[a[i]];
    print(sum);
    rep(i, 1, n) {
        int x = b[a[i]] * (sum - b[a[i]] - c[a[i]]) - c[a[i]] * (c[a[i]] - 1);
        ans += x;
        print(a[i], x);
    }
    // print(ans);
    // rep(i, 1, n) ans -= c[a[i]] * (c[a[i]] - 1);
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