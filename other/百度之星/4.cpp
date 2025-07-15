#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--);

using namespace std;
using ld = long double;
int ti;
void work() {
    int l, r;
    cin >> l >> r;
    int d = r - l;
    if (l == 1) {
        cout << 0 << endl;
    } else if (l == r) {
        cout << "infty" << endl;
    } else {
        int u = (l - 1) / (r - l);
        if (u * (r - l) < (l - 1)) u++;
        int ans = (__int128)u * (l - 1 + (l - 1 - (u - 1) * (r - l))) / 2;
        cout << ans << endl;
        // int cnt = l - 1;
        // // cnt = 0;
        // int t = ceil((l - 1) * 1.0 / d);
        // t--;
        // // cout<<t<<endl;
        // int a0 = l - 1, ad = l - t * d - 1;
        // // cout << t << ' ' << a0 << ' ' << ad << endl;
        // int y = l - t * d - 1;
        // cnt += t * (l - 1 + (l - t * d - 1)) / 2;
        // // cout << cnt << ' ' << y << endl;
        // cout << cnt << endl;
        // int lx = 1 * l, ly = lx + d;

        // cout << lx << ' ' << ly << endl;
        // rep(i, 2, 100000) {
        //     int x = i * l, y = x + i * d;
        //     // cout << x << ' ' << y <<     endl;
        //     if (ly + 1 >= x) break;
        //     cnt += (x - ly) - 1;
        //     lx = x, ly = y;
        // }
        // cout << cnt << endl;
    }
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}
