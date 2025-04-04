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
int ti = 1;
int n, k;
vector<int> c;
void work() {
    cin >> n;
    int f = 1;
    rep(i, 1, n) {
        int k;
        cin >> k;
        int la = 0;
        rep(j, 1, k) {
            int x;
            cin >> x;
            if (x <= la) f = 0;
            c.push_back(x);
            la = x;
        }
    }
    sort(c.begin(), c.end());
    rep(i, 0, (int)c.size() - 2) {
        if (c[i + 1] - c[i] != 1) f = 0;
    }
    if (f)
        print("YES");
    else
        print("NO");
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