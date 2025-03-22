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
void work() {
    cin >> n;
    int a = 1, b = (n+1)/2, c = n;
    while (1) {
        cout << '?' << ' ' << a << ' ' << b << ' ' << c << endl;
        int x;
        cin >> x;
        if (x) {
            random_device rd;   // Seed
            mt19937 gen(rd());  // Mersenne Twister
            uniform_int_distribution<int> dist(1, 3);
            
            a = b;
            b = c;
            c = x;
        } else
            break;
    }
    cout << '!' << ' ' << a << ' ' << b << ' ' << c << endl;
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