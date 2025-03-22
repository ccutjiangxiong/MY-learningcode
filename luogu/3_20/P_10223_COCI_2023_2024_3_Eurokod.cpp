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
int ti = 1;
int n;
pii a[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i].first;
    rep(i, 1, n) cin >> a[i].second;
    sort(a + 1, a + 1 + n, [](pii a, pii b) {
        if (a.first + a.second == b.first + b.second) return a.second > b.second;
        return a.first + a.second > b.first + b.second;
    });
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