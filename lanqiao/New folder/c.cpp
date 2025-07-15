#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define int long long
using namespace std;
const int N = 2e6 + 5, inf = 1e18 + 3;
int ti = 1, n;
int a[N], b[N], c[N], ord[N], ansv[N];

void work() {
    cin >> n;
    // 1) read positions + remember original index
    vector<pair<long long, int>> p(n);
    rep(i, 1, n) {
        cin >> p[i - 1].first;
        p[i - 1].second = i;
    }
    // 2) sort by position
    sort(p.begin(), p.end());
    // 3) unpack into a[1..n] and record original indices in ord[1..n]
    rep(i, 1, n) {
        a[i] = p[i - 1].first;
        ord[i] = p[i - 1].second;
    }
    // sentinel
    a[0] = -inf;
    a[n + 1] = inf;
    // build nearest‐neighbour pointers
    rep(i, 1, n) {
        long long dl = a[i] - a[i - 1];
        long long dr = a[i + 1] - a[i];
        b[i] = (dl <= dr) ? (i - 1) : (i + 1);
    }
    // merge mutual pairs and chains
    rep(i, 2, n) {
        if (b[i - 1] == i && b[i] == i - 1) {
            c[i] = c[i - 1] = (a[i] + a[i - 1]) / 2;
            int p1 = i + 1, p2 = i - 1;
            while (p1 <= n && b[p1] == p1 - 1) {
                c[p1] = c[p1 - 1];
                p1++;
            }
            while (p2 >= 1 && b[p2] == p2 + 1) {
                c[p2] = c[p2 + 1];
                p2--;
            }
        }
    }
    // 4) remap answers back to original input order
    rep(i, 1, n) { ansv[ord[i]] = c[i]; }
    // print
    rep(i, 1, n) { cout << ansv[i] << " \n"[i == n]; }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}