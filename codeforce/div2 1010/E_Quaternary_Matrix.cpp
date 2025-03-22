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
char mat[1111][1111];
int r1[N], r2[N], c1[N], c2[N];

void work() {
    queue<int> r3, r4, r5, c3, c4, c5;
    cin >> n >> m;
    rep(i, 1, max(n, m)) r1[i] = r2[i] = c1[i] = c2[i] = 0;
    rep(i, 1, n) rep(j, 1, m) cin >> mat[i][j];
    rep(i, 1, n) rep(j, 1, m) {
        int x = mat[i][j] - '0';
        if (x & 2) r1[i] ^= 1, c1[j] ^= 1;
        if (x & 1) r2[i] ^= 1, c2[j] ^= 1;
    }
    rep(i, 1, n) {
        if (r1[i] && r2[i])
            r3.push(i);
        else if (r1[i])
            r4.push(i);
        else if (r2[i])
            r5.push(i);
    }
    rep(i, 1, m) {
        if (c1[i] && c2[i])
            c3.push(i);
        else if (c1[i])
            c4.push(i);
        else if (c2[i])
            c5.push(i);
    }
    int ans = 0;
    while (r3.size() && c3.size()) {
        int i = r3.front(), j = c3.front();
        r3.pop(), c3.pop();
        ans++;
        mat[i][j] = ~(mat[i][j] - '0') + '0';
    }

    while (r4.size() && c4.size()) {
        int i = r4.front(), j = c4.front();
        r4.pop(), c4.pop();
        int x = mat[i][j] - '0';
        if (x / 2)
            mat[i][j] = '0' + x - 2;
        else
            mat[i][j] = '0' + x + 2;
        ans++;
    }
    while (r5.size() && c5.size()) {
        int i = r5.front(), j = c5.front();
        r5.pop(), c5.pop();
        int x = mat[i][j] - '0';
        if (x & 1)
            mat[i][j] = '0' + x - 1;
        else
            mat[i][j] = '0' + x + 1;
        ans++;
    }
    // while()
    cout << ans << endl;
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