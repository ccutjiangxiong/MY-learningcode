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
int x, n, m;

//// filepath: c:\Users\rein424\MY-learningcode\codeforce\div2 1010\B_Floor_or_Ceil.cpp
// ...existing code...

void work() {
    int x, n, m;
    std::cin >> x >> n >> m;
    int min = x, a = n, b = m;
    while (min > 1 && b--) {
        min = (min + 1) / 2;
    }

    while (min && a--) {
        min /= 2;
    }

    int max = x;
    a = n, b = m;
    while (max && a--) {
        max /= 2;
    }

    while (max > 1 && b--) {
        max = (max + 1) / 2;
    }

    std::cout << min << " " << max << "\n";
}
// ...existing code...
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}