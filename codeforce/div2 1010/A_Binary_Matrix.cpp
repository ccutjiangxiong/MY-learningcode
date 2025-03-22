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
int ti;
int n, m;
char mat[111][111];
int rr[N], cc[N];

void work() {
    cin >> n >> m;
    rep(i, 1, 110) rr[i] = cc[i] = 0;
    rep(i, 1, n) rep(j, 1, m) cin >> mat[i][j];
    // rep(i,1,n)rep(j,1,m) cout<<mat[i][j];
    int r = 0, c = 0;
    rep(i, 1, n) rep(j, 1, m) rr[i] ^= mat[i][j] - '0', cc[j] ^= mat[i][j] - '0';
    rep(i, 1, n) r += rr[i];
    rep(i, 1, m) c += cc[i];
    cout << max(r, c) + (abs(r - c) & 1) << endl;
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