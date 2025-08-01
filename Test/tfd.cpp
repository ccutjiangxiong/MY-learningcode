#include <bits/stdc++.h>
// #include <iostream>
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
int n, i, j;
int fun(int n, int i, int j) {
    if (n < 2) return n;
    if (min({i - 1, n - i, j - 1, n - j}) > 0) return 4 * n - 4 + fun(n - 2, i - 1, j - 1);
    if (i == 1) return j;
    if (j == n) return n - 1 + i;
    if (i == n) return 2 * n - 2 + (n - j) + 1;
    return 3 * n - 3 + (n - i) + 1;
}
void work() {
    cin >> n >> i >> j;
    print(fun(n, i, j));
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
