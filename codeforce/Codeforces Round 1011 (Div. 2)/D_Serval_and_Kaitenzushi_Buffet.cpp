#include <bits/stdc++.h>

#include <queue>

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
int n, k;
int d[N];
int vis[N];
void work() {
    cin >> n >> k;
    priority_queue<pii> pq;
    rep(i, 1, n) cin >> d[i];
    rep(i, 1, n) vis[i] = 0;
    rep(i, 1, n) pq.push({d[i], i});
    int ans = 0;
    rep(i, 1, n) {
        int x = d[i];
        int h = (n - i - k) / (k + 1);
        vis[i] = 1;
        vector<pii> gg;
        rep(i, 1, h) {
            while (vis[pq.top().second]) pq.pop();
            int u = pq.top().first;
            gg.push_back(pq.top());
            pq.pop();
            print(u, x, i);
            x += u;
        }
        ans = max(ans, x);
        for (auto y : gg) pq.push(y);
    }
    cout << ans << endl;
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