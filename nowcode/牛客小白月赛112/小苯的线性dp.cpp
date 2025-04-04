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
int n;
int a[N];
int su[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) su[i] = a[i] + su[i - 1];
    rep(k, 1, n - 2) {
        vector<int> pre(n + 1), suf(n + 2);
        rep(i, 1, n) pre[i] = max(pre[i - 1], su[i] - su[max(0ll, i - k)]);
        rem(i, n, 1) suf[i] = max(suf[i + 1], su[min(n, i + k - 1)] - su[i - 1]);
        int ans = 0;
        rep(i,1,n)ans=max(ans,max(pre[i-1],suf[i+1])-a[i]);
        cout<<ans<<' ';
    }
    cout<<max(su[n]-2*a[1],su[n-1]-a[n])<<' '<<0<<endl;
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