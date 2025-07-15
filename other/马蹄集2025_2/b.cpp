#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 2e5 + 6, inf = 1e18,mod=1e9+7;
int ti = 1;
int a[N];
int n;
void work() {
    cin >> n;
    int su = 1;
    rep(i, 1, n) cin >> a[i], (su *= a[i] + 1) %= mod;
    cout<<(su-1+mod)%mod;

}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}