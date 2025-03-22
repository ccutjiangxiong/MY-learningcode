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
int n, k;
int e[N];
piii a[N];

void work() {
    cin >> n >> k;
    rep(i, 1, 10) cin >> e[i];
    rep(i, 1, n) cin >> get<0>(a[i]);
    rep(i, 1, n) get<1>(a[i]) = i;
    sort(a + 1, a + 1 + n, [](piii a, piii b) {
        if (get<0>(a) == get<0>(b)) return get<1>(a) < get<1>(b);
        return get<0>(a) > get<0>(b);
    });
    // rep(i, 1, n) print(get<1>(a[i]));
    rep(i, 1, n) get<0>(a[i]) += e[(i - 1) % 10 + 1];
    sort(a + 1, a + 1 + n, [](piii a, piii b) {
        if (get<0>(a) == get<0>(b)) return get<1>(a) < get<1>(b);
        return get<0>(a) > get<0>(b);
    });
    rep(i, 1, k) cout << get<1>(a[i]) << ' ';
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