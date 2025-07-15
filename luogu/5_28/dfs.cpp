#include <bits/stdc++.h>
using namespace std;

// 定义常用类型与辅助宏
typedef long long ll;
typedef double db;
#define mp(a, b) make_pair(a, b)
#define x first
#define y second
#define b(a) a.begin()
#define e(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)

// 常量与数组
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 3e4;
int n, f[N + 7], g[N + 7];

// 后缀数组结构体
struct SuffixArray {
    char s[N + 7];       // 存放字符串
    int m, c[N + 7];     // 计数数组
    int tp[N + 7];       // 临时排序数组
    int rk[N + 7];       // 排名数组
    int sa[N + 7];       // 后缀数组
    int h[N + 7];        // 高度数组 (相邻后缀最长公共前缀)
    int st[N + 7][20];   // Sparse Table，用于快速查询LCP

    // 基数排序过程
    void csort() {
        for (int i = 0; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[rk[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[rk[tp[i]]]--] = tp[i];
    }

    // 构建后缀数组
    void build() {
        // 初始化数组
        memset(c, 0, sizeof c);
        memset(tp, 0, sizeof tp);
        memset(rk, 0, sizeof rk);
        memset(sa, 0, sizeof sa);
        memset(h, 0, sizeof h);
        memset(st, 0, sizeof st);

        // 初始按字符ASCII值排序
        for (int i = 1; i <= n; i++) {
            rk[i] = s[i];
            tp[i] = i;
        }
        m = 128;
        csort();

        // 逐步按照2^w长度进行排序
        for (int w = 1, p = 1; p < n; w <<= 1, m = p) {
            p = 0;
            // 将后面w个无法比较的直接排到前面
            for (int i = n - w + 1; i <= n; i++) tp[++p] = i;
            // 根据上一轮排序结果的sa来生成tp
            for (int i = 1; i <= n; i++)
                if (sa[i] > w) tp[++p] = sa[i] - w;
            // 基数排序
            csort();
            // 交换rk和tp，更新rk
            swap(rk, tp);
            rk[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) {
                // 若两段有差异则排名+1
                if (tp[sa[i]] != tp[sa[i - 1]] ||
                    tp[sa[i] + w] != tp[sa[i - 1] + w])
                    p++;
                rk[sa[i]] = p;
            }
        }

        // 计算Height数组 (相邻后缀的LCP)
        for (int i = 1, j, k = 0; i <= n; h[rk[i]] = k, i++) {
            k = max(k - 1, 0);
            j = sa[rk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
        }

        // 构建Sparse Table用于查询LCP
        for (int i = 1; i <= n; i++) st[i][0] = h[i];
        for (int w = 1; w <= 18; w++)
            for (int i = 1; i + (1 << w) - 1 <= n; i++)
                st[i][w] = min(st[i][w - 1], st[i + (1 << (w - 1))][w - 1]);
    }

    // 查询字符串下标a和b的LCP
    int Lcp(int a, int b) {
        int l = rk[a], r = rk[b];
        if (l > r) swap(l, r);
        l++;
        int k = log2(r - l + 1);
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
} a, b;

// 主逻辑处理函数
void KonnyWen() {
    // 初始化
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);

    // 读入字符串
    scanf("%s", &a.s[1]);
    n = strlen(&a.s[1]);
    // b数组存放逆序字符串
    for (int i = 1; i <= n; i++) b.s[i] = a.s[n + 1 - i];

    // 构建正、反后缀数组
    a.build();
    b.build();

    // 清空统计数组
    for (int i = 1; i <= n; i++) f[i] = g[i] = 0;

    // 枚举长度w，从1到n/2
    for (int w = 1; w <= (n >> 1); w++) {
        // 依次处理所有子串
        for (int i = w; i <= n; i += w) {
            int l = i, r = i + w;
            // LCP (正序)
            int lcp = min(w, a.Lcp(l, r));
            // LCS (逆序)，用后缀数组b计算
            int lcs = min(w - 1, b.Lcp(n - (l - 1) + 1, n - (r - 1) + 1));

            // 判断回文覆盖位置，并统计
            if (lcp + lcs >= w) {
                int cov = lcp + lcs - w + 1;
                f[r + lcp - cov]++;
                f[r + lcp]--;
                g[l - lcs]++;
                g[l - lcs + cov]--;
            }
        }
    }

    // 前缀和统计
    for (int i = 1; i <= n; i++) {
        f[i] += f[i - 1];
        g[i] += g[i - 1];
    }

    // 计算最终答案
    ll ans = 0;
    for (int i = 1; i < n; i++) ans += (ll)f[i] * g[i + 1];
    printf("%lld\n", ans);
}

// 主函数
int main() {
    int t;
    scanf("%d", &t);
    while (t--) KonnyWen();  // 多组测试
    return 0;
}
