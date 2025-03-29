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
int n;
int t[N];
struct pos {
    int x, y, v;
    bool operator<(const pos& a) const {
        if (a.v == v && x == a.x) return a.y < y;
        if (a.v == v) return a.x < x;
        return a.v < v;
    }
};

void work() {
    cin >> n;
    priority_queue<pos> pq1;
    priority_queue<pos> pq2;
    map<pos, int> mp;
    int x = 1;
    while (x * x < 2 * n) x++;
    rep(i, 0, x) rep(j, 0, x) {
        pq1.emplace(3 * i + 1, 3 * j + 1, (3 * i + 1) + (3 * j + 1));
        pq2.emplace(3 * i + 1, 3 * j + 2, (3 * i + 1) + (3 * j + 2));
        pq2.emplace(3 * i + 2, 3 * j + 1, (3 * i + 2) + (3 * j + 1));
        pq2.emplace(3 * i + 2, 3 * j + 2, (3 * i + 2) + (3 * j + 2) + 2);
        pq2.emplace(3 * i + 1, 3 * j + 1, (3 * i + 1) + (3 * j + 1));
    }

    rep(i, 1, n) {
        cin >> t[i];
        if (t[i] == 0) {
            while (mp[pq1.top()]) pq1.pop();
            auto [x, y, v] = pq1.top();
            mp[pq1.top()] = 1;
            pq1.pop();
            print(x, y);
        } else {
            while (mp[pq2.top()]) pq2.pop();
            auto [x, y, v] = pq2.top();
            mp[pq2.top()] = 1;
            pq2.pop();
            print(x, y);
        }
    }
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