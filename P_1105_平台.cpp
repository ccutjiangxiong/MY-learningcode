#include <bits/stdc++.h>
using namespace std;
int a[1111], b[1111], c[1111];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= n; i++) {
        int t = 0, s = 0;
        for (int j = 1; j <= n; j++)
            if (a[i] > a[j] && b[i] > b[j] && b[i] < c[j])
                if (a[t] < a[j]) t = j;
        cout << t << " ";
        for (int j = 1; j <= n; j++)
            if (a[i] > a[j] && c[i] > b[j] && c[i] < c[j])
                if (a[s] < a[j]) s = j;
        cout << s << endl;
    }
    return 0;
}
