#include <bits/stdc++.h>
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
int ti;
int a1, a2, a3, a4, a5;
void work() {
    cin >> a1 >> a2 >> a4 >> a5;
    int x = a1 + a2;
    int y = a5 - a4;
    int z = a4 - a2;
    if (x == y && x == z)
        print(3);
    else if (x == y || x == z || z == y)
        print(2);
    else
        print(1);
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