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
bool judge(int x) {
    string s = to_string(x);
    // renges::reverse(s);
    reverse(s.begin(), s.end());
    for (int i = 0; i + 1 <= s.size(); i++) {
        int x = (s[i] - '0') & 1;
        if ((i & 1) && x) return false;
        if ((i % 2 == 0) && x == 0) return false;
    }
    return true;
}
void work() {
    int n;
    cin >> n;
    int ans = 0;
    rep(i, 1, n) ans += judge(i);
    // rep(i, 1, n) if (judge(i)) print(i);
    // print(judge(3));
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