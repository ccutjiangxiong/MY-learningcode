#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>


#define INF 0x3f3f3f3f

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (a))

#define lc p << 1
#define rc p << 1 | 1

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 ill;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
const int N = 1e5 + 5;

int n, q, m, w[N];
struct node {
    int l, r;
    ll sum, add, mul;
} tr[N * 4];

void pushup(int p) { tr[p].sum = (tr[lc].sum + tr[rc].sum) % m; }

void pushdown(int p) {
    if (tr[p].mul != 1 || tr[p].add) {
        tr[lc].sum = (tr[lc].sum * tr[p].mul + tr[p].add * (tr[lc].r - tr[lc].l + 1)) % m;
        tr[rc].sum = (tr[rc].sum * tr[p].mul + tr[p].add * (tr[rc].r - tr[rc].l + 1)) % m;

        tr[lc].mul = (tr[lc].mul * tr[p].mul) % m;
        tr[rc].mul = (tr[rc].mul * tr[p].mul) % m;

        tr[lc].add = (tr[lc].add * tr[p].mul + tr[p].add) % m;
        tr[rc].add = (tr[rc].add * tr[p].mul + tr[p].add) % m;

        tr[p].mul = 1;
        tr[p].add = 0;
    }
}

void build(int p, int l, int r) {
    tr[p] = {l, r, 0, 0, 1};
    if (l == r) {
        tr[p].sum = w[l] % m;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

void update_mul(int p, int x, int y, int k) {
    if (x <= tr[p].l && tr[p].r <= y) {
        tr[p].sum = (tr[p].sum * k) % m;
        tr[p].mul = (tr[p].mul * k) % m;
        tr[p].add = (tr[p].add * k) % m;
        return;
    }
    pushdown(p);
    int mid = (tr[p].l + tr[p].r) >> 1;
    if (x <= mid) update_mul(lc, x, y, k);
    if (y > mid) update_mul(rc, x, y, k);
    pushup(p);
}

void update_add(int p, int x, int y, int k) {
    if (x <= tr[p].l && tr[p].r <= y) {
        tr[p].sum = (tr[p].sum + k * (tr[p].r - tr[p].l + 1)) % m;
        tr[p].add = (tr[p].add + k) % m;
        return;
    }
    pushdown(p);
    int mid = (tr[p].l + tr[p].r) >> 1;
    if (x <= mid) update_add(lc, x, y, k);
    if (y > mid) update_add(rc, x, y, k);
    pushup(p);
}

ll query(int p, int x, int y) {
    if (x <= tr[p].l && tr[p].r <= y) return tr[p].sum;
    pushdown(p);
    int mid = (tr[p].l + tr[p].r) >> 1;
    ll sum = 0;
    if (x <= mid) sum = (sum + query(lc, x, y)) % m;
    if (y > mid) sum = (sum + query(rc, x, y)) % m;
    return sum;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q >> m;

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            int d;
            cin >> d;
            update_mul(1, b, c, d);
        } else if (a == 2) {
            int d;
            cin >> d;
            update_add(1, b, c, d);
        } else if (a == 3) {
            cout << query(1, b, c) % m << endl;
        }
    }
}