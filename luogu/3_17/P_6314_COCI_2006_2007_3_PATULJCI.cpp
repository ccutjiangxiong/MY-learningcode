#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int a[N];
void work() {
    rep(i, 1, 9) cin >> a[i];
    int sum = 0;
    rep(i, 1, 9) sum += a[i];
    // print(sum);
    sum -= 100;
    rep(i, 1, 9) rep(j, 1, 9) if (a[i] + a[j] == sum && a[i] != 0 && a[j] != 0) a[i] = a[j] = 0;
    rep(i, 1, 9) if (a[i]) cout << a[i] << endl;
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