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
int n, a[N];

void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    int ans = 0, p1 = 0, p2 = 0;
    rep(i, 1, n - 1) if (a[i] > a[i + 1]) {
        ans++, p2 = i + 1;
        if (!p1) p1 = i;
    }
    if ((ans & 1) || (p1 && (a[p2] - a[p1] < p2 - p1))) print(ans / 2 + 1);
    // else cout<<ans>>1<<endl;
    else
        print(ans >> 1);
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