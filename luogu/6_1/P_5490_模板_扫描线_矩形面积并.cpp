#include <bits/stdc++.h>
#define int long long
#define inf 1e11
using namespace std;
using pii = pair<int, int>;
const int N = 3e6 + 5;

#define ls u << 1
#define rs (u << 1 | 1)

struct line {
    int x1, x2, y;
    int tag;
    bool operator<(const line &x) const { return y < x.y; }
} L[N];
struct tree {
    int l, r, cnt, len;
} tr[N];
int X[N];

void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l == r) return;
    int m = (l + r) >> 1;
    build(ls, l, m);
    build(rs, m + 1, r);
}
void pushup(int u) {
    int l = tr[u].l, r = tr[u].r;
    if (tr[u].cnt)
        tr[u].len = X[r + 1] - X[l];
    else
        tr[u].len = tr[ls].len + tr[rs].len;
}
void modify(int u, int l, int r, int tag) {
    if (l > tr[u].r || r < tr[u].l) return;
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].cnt += tag;
        pushup(u);
        return;
    }
    modify(ls, l, r, tag);
    modify(rs, l, r, tag);
    pushup(u);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        L[i] = {x1, x2, y1, 1};
        L[i + n] = {x1, x2, y2, -1};
        X[i] = x1, X[n + i] = x2;
    }
    n *= 2;
    sort(L + 1, L + 1 + n);
    sort(X + 1, X + n + 1);
    int s = unique(X + 1, X + 1 + n) - X - 1;
    build(1, 1, s - 1);
    int ans = 0;
    for (int i = 1; i < n; i++) {
        int l = lower_bound(X + 1, X + 1 + s, L[i].x1) - X;
        int r = lower_bound(X + 1, X + s + 1, L[i].x2) - X;
        modify(1, l, r - 1, L[i].tag);
        ans += tr[1].len * (L[i + 1].y - L[i].y);
    }
    cout << ans << endl;
    return 0;
}