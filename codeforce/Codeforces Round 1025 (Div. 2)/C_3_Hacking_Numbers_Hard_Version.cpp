#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define sz(a) (int)a.size()
using namespace std;
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;


template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
    fflush(stdout) or cout.flush();
}

int ti = 1, n;

void work() {
    int l = 0, r = (1 << 3) + 1;
    char ch;
    int x;
    while (cin >> ch && ch == '?') {
        cin >> x;
        int a = x - l, b = r - x + 1;
        if (x < l)
            print('<');
        else if (x >= r)
            print(">=");
        else if (a < b)
            l = x, print(">=");
        else
            r = x - 1, print('<');
        print(l, r);
    }
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