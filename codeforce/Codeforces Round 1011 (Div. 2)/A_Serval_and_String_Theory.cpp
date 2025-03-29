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
int n, k;
void work() {
    cin >> n >> k;
    string s;
    cin >> s;
    int f = 0;
    rep(i, 0, n - 2) if (s[i] != s[i + 1]) f = 1;

    string t = s;
    ranges::reverse(t);
    // print(s, t);
    if (f == 0 || (s >= t && k == 0))
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
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