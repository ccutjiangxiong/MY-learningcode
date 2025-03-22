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
int x;
void work() {
    cin >> x;
    int k = 0;
    int a1 = 0, a2 = 0;
    while ((x >> k) > 1) {
        if (x >> k & 1)
            a1 = 1 << k;
        else
            a2 = 1 << k;
        k++;
    }
    if (a1 && a2) cout << a1 + a2 << endl;
    else cout<<-2<<endl;
  
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