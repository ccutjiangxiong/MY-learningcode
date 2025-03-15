#include <bits/stdc++.h>

#include <unordered_map>

#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

int in() {
    int x;
    return (cin >> x, x);
}
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;
int n, xx, yy;
unordered_map<int, pii> mp;
int dfs(int i, int j) {
    if (i < 1 || j == i) return 0;
    __int128 x = (__int128)(i - j) * (i * i + i * j + j * j);
    print(i, j, (int)x);
    if (x == n) {
        xx = i, yy = j;
        return 0;
    }
    if (x > n) return dfs(i - 1, j);
    return dfs(i, j + 1);
}
void work() {
    cin >> n;
    if (dfs(100, 1))
        cout << xx << ' ' << yy << endl;
    else
        cout << -1 << endl;
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