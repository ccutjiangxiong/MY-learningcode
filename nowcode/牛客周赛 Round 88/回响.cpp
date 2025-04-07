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
    int la = -1;
    rep(i, 1, n) {
        if (a[i]) {
            if (la == -1)
                rem(j, i - 1, 1) a[j] = a[i] + (i - j);
            else {
                int z = abs(abs(a[i] - a[la]) - 1);
                int y = i - la - z;
                if (y <= 0 || y % 2 == 0) {
                    cout << -1 << endl;
                    return;
                }
                rep(j, la + 1, la + z) a[j] = a[j - 1] + (a[i] > a[la] ? 1 : -1);
                rep(j, la + z + 1, i - 1) a[j] = a[i] + (a[j - 1] == a[i]);
            }
            la = i;
        }
    }
    rep(i, la + 1, n) a[i] = a[i - 1] + 1;
    rep(i, 1, n) cout << a[i] << ' ';
    cout << endl;
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