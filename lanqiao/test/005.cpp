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
int gcd(int a, int b) { return __gcd(a, b); }
int gcd(int a, int b, int c) { return gcd(gcd(a, b), gcd(b, c)); }
int fun(int a, int b, int c) { return gcd(a, b) * gcd(b, c) * gcd(a, c) / gcd(a, b, c); }
int h[N];
vector<int> ans;
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    sort(a + 1, a + 1 + n);
    rep(i, 1, N) h[a[i]]++;
    int x = 0, b = 0, c = 0;
    int ma = 0;
    rem(i, N, 2) {
        vector<int> t;
        for (int j = i; j <= N; j += i) {
            rep(k, 1, h[j]) if (h[j]) t.push_back(j);
        }
        if (t.size() >= 3) {
            int y = fun(t[t.size() - 3], t[t.size() - 2], t[t.size() - 1]);
            if (y >= ma) x = t[t.size() - 3], b = t[t.size() - 2], c = t[t.size() - 1], ma = y;
        }
    }
    if (x && b && c)
        print(x, b, c);
    else
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