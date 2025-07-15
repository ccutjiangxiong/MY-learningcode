
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
int ti = 0;
void work() {
    int n, s;
    cin >> n >> s;
    int su = 0, cnt = 0;
    rep(i, 1, n) {
        int r, c;
        cin >> r >> c;
        su += c;
        if (r == 1) cnt++;
    }
    // if(su>=s+50&&cnt*2>=n) cout<<""
    cout << (cnt * 2 >= n) << ' ' << (su >= s + 50) << ' ' << endl;
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}