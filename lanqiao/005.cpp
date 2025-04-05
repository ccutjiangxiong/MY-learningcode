
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 1e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
int n;
int a[N];
int h[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i]; 
    sort(a + 1, a + 1 + n);
    rep(i, 1, n) h[a[i]]++;
    rem(i, N - 1, 2) {
        vector<int> t;
        for (int j = i; j <= N - 1; j += i) rep(k, 1, h[j]) t.push_back(j);
        if (t.size() >= 3) {
            print(t[0], t[1], t[2]);
            return;
        }
    }
    print(a[1], a[2], a[3]);
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