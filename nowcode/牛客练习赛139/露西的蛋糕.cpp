#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define sz(a) (int)(a.size())
#define me(x, a) memset(a, x, sizeof(a))
using namespace std;
#define int long long

using pii = pair<int, int>;
using vi = vector<int>;
using piii = tuple<int, int, int>;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18;
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, x;

void work() {
    cin >> n >> m >> x;
    if (m == 0) {
        print(x);
        return;
    }
    int L = 1LL << (n - m + 1);
    print(L - x + 1);
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}
