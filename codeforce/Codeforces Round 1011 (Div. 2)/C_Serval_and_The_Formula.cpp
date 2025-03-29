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
int x, y;
void work() {
    cin >> x >> y;
    if (x == y)
        cout << -1 << endl;
    else {
        int k = 0;
        while (1) {
            if (((x + k) ^ (y + k)) == x + y + 2 * k) {
                cout << k << endl;
                return;
            }
            int h = 0;
            while (((x + k) & (1 << h)) == ((y + k) & (1 << h))) {
                h++;
            }
            k += 1 << h;
            if (k > 1e9) {
                cout << -1 << endl;
                return ;
            }
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