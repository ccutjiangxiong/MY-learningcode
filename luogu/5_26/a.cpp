#include <bits/stdc++.h>
using namespace std;
int b[4];
int main(int argc, char *argv[]) {
    cin >> b[0] >> b[1] >> b[2] >> b[3];
    int fl = 1;
    for (int i = 0; i <= 1; i++)
        for (int j = 2; j <= 3; j++) {
            int x = b[i] * b[j];
            long long y = b[i] * b[j];
            cout << x << ' ' << y << endl;
            if (x != y) fl = 0;
        }
    cout << (fl ? "int" : "long long int") << endl;

    return 0;
}
