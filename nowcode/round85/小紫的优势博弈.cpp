#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n;
string s;
int p1[N], g[N], f[N];
int ans = 0;
void work() {
    cin >> n;
    cin >> s;
    rem(i, n - 1, 0) {
        int x = (f[1] % 2) * 2 + f[0] % 2;
        if (i != n - 1)
            if (x == 0 || g[x]) ans++;
        if (s[i] == '0')
            f[0]++;
        else
            f[1]++;
        g[x] = 1;
    }
    cout << ans * 1.0 / n << endl;
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