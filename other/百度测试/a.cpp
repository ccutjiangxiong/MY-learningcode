#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, K;
    cin >> n >> K;
    int sum[20][20] = {0};
    int a[20][20] = {0};
    int max_ = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            max_ = max(max_, a[i][j]);
            sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    // 二维前缀和
    auto cacul = [&](int max_x, int max_y, int min_x, int min_y) {
        return sum[max_x][max_y] - sum[min_x - 1][max_y] - sum[max_x][min_y - 1] +
               sum[min_x - 1][min_y - 1];
    };
    auto check = [&](int m)  // 真：存在k刀之内切成的所有块都小于m
    {
        if (max_ > m) return false;  // 最大单块>m，不可能使得切出来能都小于m
        int sum_col[20] = {0}, cur_col[20] = {0};
        int col[20] = {0};
        // 枚举横刀切的位置（n行有n-1个下刀的位置，用i的二进制位代表）
        for (int i = 0; i < (1 << (n - 1)); i++) {
            int fail = 0;                         // 防止横刀错误
            memset(col, 0, sizeof(col));          // 记录竖刀切的情况
            memset(cur_col, 0, sizeof(cur_col));  // 每种横刀状态下，当前列的大小
            memset(sum_col, 0, sizeof(sum_col));  // 每种横刀状态下，向右累计的大小
            vector<int> idx_row;                  // 记录当前枚举的i所代表横刀的位置
            int temp = i;
            int idx = 0;
            int count = 0;  // 记录切的刀数
            while (temp) {
                idx++;
                if (temp & 1) {
                    idx_row.push_back(idx);
                    count++;
                }
                temp /= 2;
            }
            if (count > K) continue;  // 横刀已经超过k了
            idx_row.push_back(n);  // 最后一刀首尾，容易知道如果切的位置x 第x行x的下边界

            int top = 1;
            // 枚举每一列横刀位置之间的所提供的重量再加上之前累加的重量，超过就切
            for (int j = 1; j <= n; j++) {
                top = 1;  // 当前块的最小行下标
                // 对于j列，从上到下枚举计算i状态下产生的count+1个块
                for (int k = 0; k < idx_row.size(); k++) {
                    int down = idx_row[k];             // 当前块的最大行下标
                    int now = cacul(down, j, top, j);  // 当前宽度为1的块的重量
                    if (now > m)  // 当前横刀的最小单位超过m,横刀重新切
                    {
                        fail = 1;
                        break;
                    }
                    sum_col[k] += now;  // 向右累加
                    cur_col[k] = now;  // 缓存当前列的数据，防止被切，以形成新的块
                    if (col[j - 1])    // 前一列是否被切断了
                    {  // 这种情况存在于当前列的上层块已经满足切的条件了
                        sum_col[k] = now;
                    }
                    if (sum_col[k] >
                        m)  // 第k块j列累加超过m了，说明当前列不能累加，前一个位置切掉，当前列自立门户
                    {
                        col[j - 1] = 1;  // 记录竖切的位置
                        sum_col[k] = now;
                        // 更新k横块以上的第j列的重量，不再累加前面的
                        for (int p = 0; p < k; p++) {
                            sum_col[p] = cur_col[p];
                        }
                    }
                    top = down + 1;
                }
                if (fail == 1) break;
            }
            if (fail == 1) continue;
            for (int p = 1; p <= n - 1; p++) {
                if (col[p]) count++;
            }
            if (count <= K) return true;
        }
        return false;  // 没有一个组合能使得切出来的所有块都小于m
    };
    int l = 0, r = 2000 * 15 * 15;
    // 枚举答案
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m))  // 存在一种切法 所有块都小于m,说明还可以再切小一些
        {
            r = m - 1;
        } else  // 不管怎么切 都不满足所有块小于m，m太小了
        {
            l = m + 1;
        }
    }
    cout << l;
    return 0;
}
