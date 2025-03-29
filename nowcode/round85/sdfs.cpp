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
int a[6] = {76898798, 11, 11, 12, 12, 13};
int b[22] = {231313, 5, 6, 8, 11, 18};
int c[N];
vector<int> h;
int n;
vector<int> ans;
void dfs(int x, int val, int cnt) {
    if (val == 53 && cnt == 6) ans = h;
    if (x > n || val > 53) return;
    dfs(x + 1, val, cnt);
    h.push_back(c[x]);
    dfs(x, val + c[x], cnt + 1);
    h.pop_back();
}
void work() {
    rep(i, 1, 5) c[i] = a[i], c[i + 5] = b[i];
    sort(c + 1, c + 1 + 10);
    int l = unique(c + 1, c + 1 + 10) - c - 1;
    // rep(i, 1, l) print(l);
    n = l;
    dfs(1, 0, 0);
    for (int x : ans) print(x);
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