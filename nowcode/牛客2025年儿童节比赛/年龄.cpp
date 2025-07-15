#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

int main() {
    LL m = 0, result = 0;
    cin >> m;
    vector<LL> d(m);
    for (LL b = 1; b <= m; ++b)
        for (LL a = b; a <= m; a += b) {
            // a = b * p;
            ++d[a - b];
        }
    for (LL i = 0; i < m; ++i) result += d[i] * (d[i] - 1) / 2;
    cout << result << '\n';
}
