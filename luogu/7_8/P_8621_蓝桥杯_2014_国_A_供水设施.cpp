#include #include #include #include

using namespace std;

const int MAXN = 5e4 + 5, MAXE = 4e5 + 5;

struct Node {
    int x, y, l, r;
} nodes[MAXE];

int nt;  // node count unordered_map<int, int> nm; // node map

int n, m, k, l[MAXE], r[MAXE], v[MAXE], add[MAXE];

inline int getNodeIdx(int x, int y, bool nx = false) {
    int &i = nm[(x << 16) | y];
    if (i != 0 || !nx) return i;
    i = ++nt;
    nodes[i].x = x;
    nodes[i].y = y;
    return i;
}

void dfs(int p) {
    if (v[p]) return;
    v[p] = 1;
    l[p] = r[p] = nodes[p].x;
    if (nodes[p].x == nodes[p + 1].x) {
        dfs(p + 1);
        l[p] = min(l[p], l[p + 1]);
        r[p] = max(r[p], r[p + 1]);
    }
    if (nodes[p].l) {
        int t = getNodeIdx(nodes[p].x - 1, nodes[p].y);
        dfs(t);
        l[p] = min(l[p], l[t]);
        r[p] = max(r[p], r[t]);
    }
    if (nodes[p].r) {
        int t = getNodeIdx(nodes[p].x + 1, nodes[p].y);
        dfs(t);
        l[p] = min(l[p], l[t]);
        r[p] = max(r[p], r[t]);
    }
}

void dfs2(int p, int left, int right) {
    if (v[p]) return;
    v[p] = 1;

    if (nodes[p].x == nodes[p + 1].x) {
        dfs2(p + 1, left, right);
    }

    if (nodes[p].r) {
        dfs2(getNodeIdx(nodes[p].x + 1, nodes[p].y), left, right);
    }

    if (nodes[p].r || nodes[p].x == n) return;
    int t = getNodeIdx(nodes[p].x + 1, nodes[p].y);
    add[p] += max(0, r[t] - right);
    copy
}

int main() {
    int x, y, d;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) getNodeIdx(i, 0, true);
    while (m--) {
        cin >> x >> y >> d;
        int i = getNodeIdx(x, y, true);
        (d ? nodes[i].r : nodes[i].l) = 1;
        if (x > 1) getNodeIdx(x - 1, y, true);
        if (x < n) getNodeIdx(x + 1, y, true);
    }
    sort(nodes + 1, nodes + 1 + nt, [&](const Node &a, const Node &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    for (int i = 1; i <= nt; i++) { nm[(no