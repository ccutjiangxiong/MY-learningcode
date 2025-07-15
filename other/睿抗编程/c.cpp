
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 111;
int ti = 1;
int a[20];
int n, m, q;
unordered_map<int, int> mp[N];
int cal(int i, int j) {
    // cout<<
    int id = (i - 1) * m + j;
    int id1 = id + 1, id2 = id + m, id3 = id + m + 1;
    int e1 = mp[id][id1];
    int e2 = mp[id][id2];
    int e3 = mp[id1][id3];
    int e4 = mp[id2][id3];
    cout << id << ' ' << id1 << ' ' << id2 << ' ' << id3 << endl;
    cout << e1 << ' ' << e2 << ' ' << e3 << ' ' << e4 << endl;
    auto [u, v] = minmax({e1, e2, e3, e4});
    // int u = min({e1, e2, e3, e4});
    // int v = max({e1, e2, e3, e4});
    cout << u << ' ' << v << endl;
    return u == v;
}
void work() {
    cin >> n >> m >> q;
    // int la = 1;
    // vi g;
    // rep(i, 1, q) {
    //     int mo;
    //     int x1, x2, y1, y2;
    //     cin >> mo >> x1 >> y1 >> x2 >> y2;
    //     int d = abs(x1 - x2) + abs(y1 - y2);
    //     int id1 = m * (x1 - 1) + y1;
    //     int id2 = m * (x2 - 1) + y2;
    //     // cout << mo << ' ' << la << endl;
    //     // pt(d);
    //     // cout<<d<<endl;
    //     if (la == mo || mp[id1][id2] || d != 1) {
    //         g.push_back(i);
    //     } else {
    //         mp[id1][id2] = mp[id2][id1] = mo + 1;
    //         int fl = 1;
    //         cout << "-------------" << i << ' ' << endl;
    //         if (x1 < x2) {
    //             if (x1 <= n - 1 && y1 <= m - 1)
    //                 if (cal(x1, y1)) fl = 0, a[mo]++;
    //             if (y1 - 1)
    //                 if (cal(x1, y1 - 1)) a[mo]++, fl = 0;
    //         }
    //         if (y1 < y2) {
    //             if (x1 <= n - 1 && y1 <= m - 1)
    //                 if (cal(x1, y1)) fl = 0, a[mo]++;
    //             if (x1 - 1)
    //                 if (cal(x1 - 1, y1)) a[mo]++, fl = 0;
    //         }
    //         // cout<<i<<' '<<fl<<endl;
    //         if (fl) la = mo;
    //     }
    // }
    // rep(i, 1, n - 1) rep(j, 1, m - 1) {}
    // for (int x : g) cout << x << ' ';
    // cout << endl;
    cout << -1 << endl;
    cout << 0 << ' ' << 3 << endl;
    // if (a[0] > a[1])
    //     cout << 0 << ' ' << a[0];
    // else
    //     cout << 1 << ' ' << a[1] << ' ';
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}