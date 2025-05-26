
#include <iostream>

using namespace std;

const int N = 5555;
int n, m, cnt;
struct dlx {
    int u, d, l, r;
    int row, col;
} a[N];
int h[N];
int s[N];
int ans[N];

void init() {
    for (int y = 0; y <= m; y++) {
        a[y].u = a[y].d = y;
        a[y].l = y - 1, a[y].r = y + 1;
    }
    a[0].l = m, a[m].r = 0;
    cnt = m;
}
void link(int x, int y) {
    a[++cnt].row = x, a[cnt].col = y;
    s[y]++;
    a[cnt].u = a[y].u, a[cnt].d = y;
    a[a[y].u].d = cnt;
    a[y].u = cnt;
    if (h[x] == 0)
        h[x] = a[cnt].r = a[cnt].l = cnt;
    else {
        a[cnt].l = a[h[x]].l;
        a[cnt].r = h[x];
        a[a[h[x]].l].r = cnt;
        a[h[x]].l = cnt;
    }
}
void remove(int y) {
    a[a[y].r].l = a[y].l;
    a[a[y].l].r = a[y].r;
    for (int i = a[y].d; i != y; i = a[i].d)
        for (int j = a[i].r; i != j; j = a[j].r)
            a[a[j].u].d = a[j].d, a[a[j].d].u = a[j].u, s[a[j].col]--;
}
void resume(int y) {
    a[a[y].r].l = a[a[y].l].r = y;
    for (int i = a[y].u; i != y; i = a[i].u)
        for (int j = a[i].l; j != i; j = a[j].l) a[a[j].u].d = a[a[j].d].u = j, s[a[j].col]++;
}
bool dance(int dep) {
    if (a[0].r == 0) {
        for (int i = 0; i < dep; i++) cout << ans[i] << ' ';
        return true;
    }
    int y = a[0].r;
    for (int i = a[0].r; i; i = a[i].r) {
        if (s[i] < s[y]) y = i;
    }
    remove(y);
    for (int i = a[y].d; i != y; i = a[i].d) {
        ans[dep] = a[i].row;
        for (int j = a[i].r; j != i; j = a[j].r) remove(a[j].col);
        if (dance(dep + 1)) return true;
        for (int j = a[i].l; j != i; j = a[j].l) resume(a[j].col);
    }
    resume(y);
    return false;
}
int main() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int tmp;
            cin >> tmp;
            if (tmp) link(i, j);
        }
    if (!dance(0)) cout << "No Solution!" << endl;
}
