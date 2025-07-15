#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--);

using namespace std;
int ti;
void work() {
    int n, s;
    cin >> n >> s;
    rep(i, 1, n) {
        int x;
        cin >> x;
        if (x > s) {
            int y = (x + s) / 2;
            if (y * 2 < x + s) y++;
            s = y;
        }
        // cout << x << ' ' << s << endl;
    }
    cout << s << endl;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}
