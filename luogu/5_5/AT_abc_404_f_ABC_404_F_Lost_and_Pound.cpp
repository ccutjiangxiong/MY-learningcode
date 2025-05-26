#include <bits/stdc++.h>
#define gc getchar
using namespace std;
template <typename T>
void read(T &x) {
    x = 0;
    int f = 1;
    char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = gc();
    }
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
    x *= f;
}
int n, t, m, k, cnt, a[40], rnd, hm, tot;
long double f[40][100], mx, now;
void sch(int rst) {
    if (cnt > n) return;
    if (!rst) {
        now = 0;
        for (int i = 1; i <= cnt; i++)
            now += (long double)1.0 * f[rnd - 1][hm + a[i]] / n;  // 第 i 个按钮是关键按钮
        mx = max(
            mx, now + (long double)1.0 * (n - cnt) * f[rnd - 1][hm] / n);  // 没能按中关键按钮的情况
        return;
    }
    for (int i = min(a[cnt], rst); i; i--) a[++cnt] = i, sch(rst - i), cnt--;  // 钦定不减，进行搜索
}
int main() {
    read(n), read(t), read(m), read(k), a[0] = 1e9;
    for (int i = 0; i <= t; i++)
        for (int j = k; j <= 80; j++) f[i][j] = 1;  // 边界初始化
    for (int i = 1; i <= t; i++) {
        rnd = i;
        for (int j = 0; j < k; j++) hm = j, mx = cnt = 0, sch(m), f[i][j] = mx;
    }
    printf("%.20LF", f[t][0]);
    return 0;
}