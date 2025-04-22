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
string s, t;
int n;
Kmp
    
bool check(int x) {
    
}
bool judge(int x) {
    int l = 1, r = n - x;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) return true;
    }
    // rep(i, 1, n) dp[i][1] = dp[i][0] = -inf;
    // dp[0][0] = -1;
    // rep(i, 1, n - x) {
    //     int z = dp[i - 1][1], y = dp[i - 1][0];
    //     // dp[i][0]=
    //     if (t[i - 1] == s[z + 1]) dp[i][1] = z + 1;
    //     if (t[i - 1] == s[y + 1]) dp[i][0] = y + 1;
    //     else dp[i][1]=dp[i-1][1];
    //     if (max(dp[i][1], dp[i][0]) == x) return true;
    // }

    // return false;

}
void work() {
    cin >> s;
    t = s;
    reverse(t.begin(), t.end());
    n = s.size();
    int l = 0, r = n / 2;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (judge(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
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