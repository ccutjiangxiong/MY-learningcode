#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 2e5 + 6, inf = 1e18;
int ti = 1;
int a[N];
int n;
void work() {
    cin >> n;
    int su = 0;
    rep(i, 1, n) cin >> a[i], su += a[i];
    int su2 = 0;
    int p = 1;
    while (p <= n) {
        // cout << p << endl;
        su2 += a[p];
        p++;
        if (p <= n) su2 += a[p];
        p += 3;
    }
    // cout << su2 << endl;
    cout << su2 * 2 - su;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}