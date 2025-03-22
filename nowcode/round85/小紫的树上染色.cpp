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
pii p[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }
vector<int> q;
set<int> h;
int fl = 0;
void work() {
    cin >> n;
    vector<pair<long long, long long>> segs(n);
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
    }
    sort(segs.begin(), segs.end());

    vector<int> color(n, 0);
    long long last1 = -1, last2 = -1;
    for (int i = 0; i < n; i++) {
        if (segs[i].first > last1) {
            color[i] = 1;
            last1 = segs[i].second;
        } else if (segs[i].first > last2) {
            color[i] = 2;
            last2 = segs[i].second;
        } else {
            cout << -1 << "\n";
            return;
        }
    }
    if (count(color.begin(), color.end(), 1) == 0) {
        for (int &c : color) {
            if (c == 2) c = 1;
        }
    }

    vector<int> purples;
    for (int i = 0; i < n; i++) {
        if (color[i] == 1) {
            purples.push_back(i + 1);
        }
    }

    cout << purples.size() << "\n";
    for (int i = 0; i < (int)purples.size(); i++) {
        cout << purples[i] << (i + 1 < (int)purples.size() ? ' ' : '\n');
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