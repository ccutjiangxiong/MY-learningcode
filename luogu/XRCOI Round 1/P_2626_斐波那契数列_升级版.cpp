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
int ti = 1;
int n;

void work() {
    cin >> n;
    // rep()
    int a = 0, b = 1, c = 1;
    rep(i, 1, n - 1) c = a + b, a = b, b = c, c %= 1 << 31;
    // euler(N);
    string s;
    // print(c);
    s += to_string(c) + '=';
    int g = c;
    rep(i, 2, g) {
        while (c % i == 0 && c > 1) s += to_string(i) + '*', c /= i;
        if (c == 1) break;
    }
    cout << s.substr(0, s.length() - 1) << endl;

    // print(c);
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