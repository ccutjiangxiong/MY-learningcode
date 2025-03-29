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
int x, y, a;
void work() {
    cin >> x >> y >> a;
    int cnt = 0;
    a = a - (a) / (x + y) * (x + y) + x + y;
    while (a >= 0) {
        if (cnt % 2 == 0)
            a -= x;
        else
            a -= y;
        cnt++;
    }
    if (cnt & 1)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
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