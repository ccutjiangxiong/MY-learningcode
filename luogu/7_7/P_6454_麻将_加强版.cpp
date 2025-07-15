#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最大元素数量
static const int MAXN = 5005;

// 全局变量
int n;                 // 数列长度
int a[MAXN], b[MAXN];  // 原始数组和辅助数组
int lft[MAXN][2],  // 从左到右的 DP 状态：lft[i][0] = 前 i 个元素整体“操作”次数累加，lft[i][1] = 第
                   // i 个元素剩余 b[i]
    rgt[MAXN][2];  // 从右到左的 DP 状态

// 快速读入一个整数（支持负数）
ll readInt() {
    ll x = 0;
    int c = getchar();
    while (c != '-' && !isdigit(c)) c = getchar();
    bool neg = (c == '-');
    if (neg) c = getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return neg ? -x : x;
}

// 检查当前 a[] 配置是否满足题意
bool check() {
    // 1) 从左到右模拟
    copy(a + 1, a + 1 + n, b + 1);
    int posL = n - 1;  // 如果遇到 b[i]<0 则记录断点
    for (int i = 1; i <= n - 2; ++i) {
        b[i] -= lft[i - 1][0];
        if (b[i] < 0) {
            posL = i;
            break;
        }
        b[i] %= 3;
        lft[i][0] = lft[i - 1][1] + b[i];
        lft[i][1] = b[i];
    }

    // 2) 从右到左模拟
    copy(a + 1, a + 1 + n, b + 1);
    int posR = 2;  // 如果遇到 b[i]<0 则记录断点
    for (int i = n; i >= 3; --i) {
        b[i] -= rgt[i + 1][0];
        if (b[i] < 0) {
            posR = i;
            break;
        }
        b[i] %= 3;
        rgt[i][0] = rgt[i + 1][1] + b[i];
        rgt[i][1] = b[i];
    }

    // 3) 在 [posR-1, posL] 区间尝试拆分点
    for (int i = posR - 1; i <= posL; ++i) {
        int x = a[i] - lft[i - 1][0] - rgt[i + 2][1];
        int y = a[i + 1] - lft[i - 1][1] - rgt[i + 2][0];
        if (x >= 0 && y >= 0) {
            // (x % 3, y % 3) = (2,0) 或 (0,2) 时成立
            if ((x % 3 == 2 && y % 3 == 0) || (x % 3 == 0 && y % 3 == 2)) {
                return true;
            }
        }
    }

    // 4) 特殊情况：若所有元素均为偶数，则也算 VALID
    bool allEven = true;
    for (int i = 1; i <= n; ++i) {
        if (a[i] & 1) {
            allEven = false;
            break;
        }
    }
    return allEven;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    n = readInt();
    int k = readInt();
    // 读入 k 次操作：对下标 idx 计数加一
    while (k--) {
        int idx = readInt();
        ++a[idx];
    }

    vector<int> answer;
    // 枚举每个位置，试探性地加一后调用 check()
    for (int i = 1; i <= n; ++i) {
        ++a[i];
        if (check()) answer.push_back(i);
        --a[i];
    }

    // 输出结果
    cout << answer.size() << "\n";
    for (int x : answer) cout << x << " ";
    cout << "\n";
    return 0;
}