#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    stringstream s;
    s.precision(0);
    s << fixed << pow(2.0L, n + 1);  // 将pow后存进去
    string a = s.str();              // 放到a中，这里个位数只能是2,4,8,6
    a[a.length() - 1]--;
    a[a.length() - 1]--;  // 减去2，不会影响上一行
    cout << a << endl;
    return 0;
}
