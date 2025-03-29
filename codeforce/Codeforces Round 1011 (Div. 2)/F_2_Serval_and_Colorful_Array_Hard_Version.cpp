#include <bits/stdc++.h>

#include <functional>

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
int n, m;
void work() {
    cin >> n >> m;
    vector<int> indices(m);
    function<void(int, int)> dfs = [&](int depth, int start) {
        if (depth == m) {
            for (int i = 0; i < m; i++) cout << indices[i] << " ";
            cout << "\n";
            return;
        }
        for (int i = start; i <= n; i++) {
            indices[depth] = i;
            dfs(depth + 1, i + 1);
        }
    };

    dfs(0, 1);
    dfs(0, 1);
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