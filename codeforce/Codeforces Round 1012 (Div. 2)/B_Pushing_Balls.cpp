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
int n, m;
char mat[55][55];
int mm[55][55];
void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> mat[i][j];
    rep(i, 1, n) rep(j, 1, m) mm[i][j] = 0;
    rep(i, 1, n) rep(j, 1, m) if (j == 1 || mat[i][j] == '1' && mat[i][j - 1] == '1') mm[i][j] = 1;
    else break;
    rep(j, 1, m) rep(i, 1, n) if (i == 1 || mat[i][j] == '1' && mat[i - 1][j] == '1') mm[i][j] = 1;
    else break;
    int ans = 0;
    rep(i, 1, n) rep(j, 1, m) if (mat[i][j] == '1' && mm[i][j] == 0) ans = 1;
    if (ans == 0)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
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