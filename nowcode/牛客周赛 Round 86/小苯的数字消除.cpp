#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
string s;
void work() {
    cin >> n >> s;
    int ans = 0;
    string t;
    for (int i = 0; i + 1<= s.size(); i++)
        if (i + 1 != s.size() &&s[i] == s[i + 1])
            i++;
        else {
            t += s[i];
            while (t.size() >= 2 && t[t.size() - 1] == t[t.size() - 2]) t.pop_back(), t.pop_back();
        }
    // print(t);
    if (t.empty())
        cout << 0 << endl;
    else
        cout << t.size() / 2 << endl;
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