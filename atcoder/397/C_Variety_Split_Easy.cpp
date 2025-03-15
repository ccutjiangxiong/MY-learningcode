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
int a[N];
set<int> s1, s2;
int pre[N], suf[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) {
        s1.insert(a[i]);
        pre[i] = s1.size();
    }
    rem(i, n, 1) {
        s2.insert(a[i]);
        suf[i] = s2.size();
    }
    int ans = 0;
    rep(i, 0, n) ans = max(ans, pre[i] + suf[i +1]);
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