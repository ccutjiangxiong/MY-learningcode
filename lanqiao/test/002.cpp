#include <bits/stdc++.h>

// #include <iomanip>

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
int x = 343720, y = 233333;
void work() {
    int dx = 15, dy = 17;
    int k = 1;
    while (1) {
        if (k * dx % x == 0 && k * dy % y == 0) break;
        k++;
    }

    cout << fixed << setprecision(2) << 2 * sqrt(k * k * dx * dx + k * k * dy * dy) << endl;
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