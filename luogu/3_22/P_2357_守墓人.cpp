#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
int n, f;
int a[N];
#define lc p << 1
#define rc (p << 1 | 1)
struct Node {
    int l, r, sum, add;
} tr[N * 4];
int w[N];
inline int &sum(int a) { return tr[a].sum; }
inline int &add(int a) { return tr[a].add; }
inline int &l(int a) { return tr[a].l; }
inline int &r(int a) { return tr[a].r; }
void pushup(int p) { sum(p) = sum(rc) + sum(lc); }
void build(int p, int l, int r) {
    tr[p] = {l, r, w[l], 0};
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
    pushup(p);
}
void pushdown(int p) {
    if (add(p)) {
        sum(lc) += add(p) * (r(lc) - l(lc) + 1);
        sum(rc) += add(p) * (r(rc) - l(rc) + 1);
        add(lc) += add(p);
        add(rc) += add(p);
        add(p) = 0;
    }
}
void update(int p, int x, int y, int k) {
    if (x <= l(p) && y >= r(p)) {
        sum(p) += (r(p) - l(p) + 1) * k;
        add(p) += k;
        return;
    }
    int m = (l(p) + r(p)) >> 1;
    pushdown(p);
    if (x <= m) update(lc, x, y, k);
    if (y > m) update(rc, x, y, k);
    pushup(p);
}
int query(int p, int x, int y) {
    if (x <= l(p) && y >= r(p)) return sum(p);
    int m = (l(p) + r(p)) >> 1;
    pushdown(p);
    int sum = 0;
    if (x <= m) sum += query(lc, x, y);
    if (y > m) sum += query(rc, x, y);
    return sum;
}
void work() {
    cin >> n >> f;
    rep(i, 1, n) cin >> w[i];

    build(1, 1, n);
    while (f--) {
        int m;
        cin >> m;
        if (m == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            update(1, l, r, k);
        }
        if (m == 2) {
            int k;
            cin >> k;
            update(1, 1, 1, k);
        }
        if (m == 3) {
            int k;
            cin >> k;
            update(1, 1, 1, -k);
        }
        if (m == 4) {
            int l, r;
            cin >> l >> r;
            cout << query(1, l, r) << endl;
        }
        if (m == 5) cout << query(1, 1, 1) << endl;
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