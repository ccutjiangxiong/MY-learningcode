#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n;
set<int> s[N];
int dfa[N], fa[N];
int dis[2222][2222];
void work() {   rep(i, 1, n) {
        dfa[i] = inf;
        rep(j, 1, n) dfa[i] = inf;
        rep(j, 1, n) if (j != i) s[j].insert(j);
        cout << "? "<< 2 << ' ' << i << '\n';
        int x, y;
        cin >> x;
        rep(i, 1, x) {
            cin >> y;
            s[i].erase(y);
        }
    }
    rep(i, 1, n) for (int u : s[i]) {
        cout << "? " << 1 << ' ' << i << ' ' << u << '\n';
        cin >> dis[i][u];
    }
    rep(i, 1, n) for(int u : s[i]) if (dis[i][u] < dfa[i]) fa[i] = u, dfa[i] = dis[i][u];
    cout <<"! "<< ' ';
    rep(i, 2, n) cout << 2 << ' ' << fa[i];
    cout << endl;
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