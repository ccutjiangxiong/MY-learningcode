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
int n, a[N], pre[N];
multiset<int> s;
void work() {
    cin >> n;
    int ans = inf;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
    rep(i, 1, n) rep(j, i, n) s.insert(pre[j] - pre[i - 1]);
    rep(i, 1, n - 1) {
        rep(j, i, n) {
            auto p = s.find(pre[j] - pre[i - 1]);
            s.erase(p);
        }
        rep(j, 1, i) {
            int k = pre[i]-pre[j - 1];
            auto p = s.lower_bound(k);
            if (p != s.end()) ans = min(ans, abs(*p - k));
            if (p != s.begin()) p--, ans = min(ans, abs(*p - k));
        }
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