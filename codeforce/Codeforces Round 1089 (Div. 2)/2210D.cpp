#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string s, t;
        cin >> s >> t;

        vector<int> ps(n), pt(n);

        // 前缀和
        ps[0] = (s[0] == '(' ? 1 : -1);
        pt[0] = (t[0] == '(' ? 1 : -1);

        for (int i = 1; i < n; i++) {
            ps[i] = ps[i - 1] + (s[i] == '(' ? 1 : -1);
            pt[i] = pt[i - 1] + (t[i] == '(' ? 1 : -1);
        }

        if (ps == pt)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}