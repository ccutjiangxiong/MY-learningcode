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
int n;
int a[N];

void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int a1 = 1, a2 = 1;
    int ans = 0;
    rep(i, 1, n) {
        int p1 = 0, p2 = 0;
        rep(j, i + 1, n) {
            if (a[i] > a[j]) p1++;
            if (a[i] < a[j]) p2++;
            if (p1 - p2 > ans) ans = p1 - p2, a1 = i, a2 = j;
        }
    }
    cout << a1 << ' ' << a2 << endl;
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