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
int a[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];

    if (a[1] == 0) {
        int mi = inf;
        rep(i, 3, n) mi = min(mi, a[i]);
        if (mi == 0) {
            print(3);
            print(1, 2);
            print(2, n - 1);
            print(1, 2);
        } else {
            print(2);
            print(1, 2);
            print(1, n - 1);
        }
    } else {
        int mi = inf;
        rep(i, 2, n) mi = min(mi, a[i]);
        if (mi == 0) {
            print(2);
            print(2, n);
            print(1, 2);
        } else {
            print(1);
            print(1, n);
        }
    }
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