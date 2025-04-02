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
int ti = 1;
int n;
double d;
string s;
int ans[N];
void fun() {
    int c = 0;
    rep(i, 1, 22222) {
        ans[i] *= 2;
        ans[i] += c;
        c = 0;
        if (ans[i] >= 10) c = 1, ans[i] %= 10;
    }
}
void coo() {
    int h = 11111;
    rem(i, 22222, 11111) if (ans[i] != 0) {
        h = i;
        break;
    }
    rem(i, h, 11111) cout << ans[i];
    cout << endl;
}
void work() {
    cin >> n >> s;
    string t2 = s.substr(s.find('.') + 1, s.size());
    string t1 = s.substr(0, s.find('.'));
    reverse(t1.begin(), t1.end());
    for (int i = 0; i + 1 <= t1.size(); i++) ans[i + 11111] = t1[i] - '0';
    for (int i = 0; i + 1 <= t2.size(); i++) ans[11111 - i - 1] = t2[i] - '0';
    rep(i, 1, n) fun();
    if (ans[11110] >= 5) ans[11111]++;
    rep(i, 11111, 22222) if (ans[i] >= 10) ans[i + 1]++, ans[i] %= 10;
    coo();
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