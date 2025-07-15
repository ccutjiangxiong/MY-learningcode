
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
int ti = 1;
void ask(int x, int y, int z) {
    if (x > 7 || (x == 7 && y > 11)) {
        cout << "Too late!" << endl;
    } else if (x < 6 || (x == 6 && y <= 20)) {
        if (z == 1800) cout << "Ok!" << endl;
        if (z < 1800) cout << "Need more!" << endl;
        if (z > 1800) cout << "^_^" << endl;
    } else {
        if (z == 2000) cout << "Ok!" << endl;
        if (z < 2000) cout << "Need more!" << endl;
        if (z > 2000) cout << "^_^" << endl;
    }
}
void work() {
    int n;
    cin >> n;
    rep(i, 1, n) {
        int x, y, z;
        cin >> x >> y >> z;
        ask(x, y, z);
    }
    // rep(i, 1, 12) ask(i, 11, 2000);
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}