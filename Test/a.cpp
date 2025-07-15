#include <bits/stdc++.h>
#define db double
#define rtn return
using namespace std;

long long a[6], b, c, d, n, m, nn, mm;

signed main() {
    cin >> a[1] >> a[2] >> a[3] >> a[4];

    for (int i = 1; i <= 2; i++) {
        for (int j = 3; j <= 4; j++) {
            int res = a[i] * a[j];
            long long res2 = a[i] * a[j];
            cout << res << ' ' << res2 << endl;
            if (res != res2) {
                cout << "long long int";
                return 0;
            }
        }
    }

    cout << "int";

    return 0;
}
