#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 2e6 + 6, inf = 1e18, mod = 1e9 + 7;
int ti = 1;
int a[N];
int n;
void work() {
    cin >> n;
    int su = 0;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n - 1) su += (n - (i + 1) + 1);
    cout << su << endl;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}