#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
int n, x;
int ans[N];
void work() {
    cin >> n >> x;
    rep(i, 1, n) ans[i] = 0;
    vector<int> h;
    rem(k, 32, 0) {
        if ((x >> k) & 1) h.push_back(1 << k), x -= 1 << k;
        if (h.size() == n) {
            h[n - 1] += x;
            break;
        }
    }
    while (h.size() < n) h.push_back(0);
    rep(i, 0, n - 1) cout << h[i] << ' ';
    cout << endl;
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