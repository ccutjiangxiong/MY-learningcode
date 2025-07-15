#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 单元格（Cell）结构：保存数值 v 及其在矩阵中的坐标 (x, y)
struct Cell {
    int v, x, y;
};
// 查询（Query）结构：保存子矩形左上 (x1,y1)、右下 (x2,y2) 以及第 k 小的 k，和该查询的原始编号 id
struct Query {
    int x1, y1, x2, y2, k, id;
};

int n, q;                 // 矩阵大小 n 和查询个数 q
vector<Cell> cells;       // 将所有单元格展平并按数值排序
vector<Query> Q;          // 存放所有查询
vector<int> lo, hi, ans;  // 并行二分搜索的下界 lo、上界 hi 和答案 ans

// 2D 版的 Fenwick 树，用于动态维护前缀和，支持点更新和矩形查询
struct Fenwick2D {
    int n;
    vector<vector<int>> t;
    Fenwick2D(int _n) : n(_n), t(n + 1, vector<int>(n + 1, 0)) {}

    // 在 (x,y) 位置加上 v
    void update(int x, int y, int v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= n; j += j & -j) t[i][j] += v;
    }

    // 查询 (1,1) 到 (x,y) 的前缀和
    int query(int x, int y) {
        int s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }

    // 查询任意子矩形 (x1,y1) 到 (x2,y2) 的和
    int rect(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 读入 n, q
    cin >> n >> q;

    // 读入矩阵并展平成 cells 数组
    cells.reserve(n * n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int v;
            cin >> v;
            cells.push_back({v, i, j});
        }
    }
    // 按数值从小到大排序
    sort(cells.begin(), cells.end(), [](auto &a, auto &b) { return a.v < b.v; });

    // 初始化查询数组和并行二分的 lo/hi 数组
    Q.resize(q);
    lo.assign(q, 0);           // 最小可能答案
    hi.assign(q, 1000000000);  // 最大可能答案
    ans.assign(q, 0);

    // 读入所有查询参数
    for (int i = 0; i < q; i++) {
        auto &qq = Q[i];
        cin >> qq.x1 >> qq.y1 >> qq.x2 >> qq.y2 >> qq.k;
        qq.id = i;  // 记录原始查询编号
    }

    // 并行二分搜索主体
    vector<pair<int, int>> mid_id;  // 存储（中间值 mid，对应查询索引）
    Fenwick2D bit(n);               // 构造一个 n*n 的 2D Fenwick 树

    bool changed = true;
    while (changed) {
        changed = false;
        mid_id.clear();

        // 对每个查询，如果 lo<hi，就计算当前二分中点 m 并加入待处理列表
        for (int i = 0; i < q; i++) {
            if (lo[i] < hi[i]) {
                int m = lo[i] + (hi[i] - lo[i]) / 2;
                mid_id.emplace_back(m, i);
                changed = true;
            }
        }
        if (!changed) break;

        // 按中点 m 增序处理，保证一次 Fenwick 扫描能复用
        sort(mid_id.begin(), mid_id.end());

        // 重置 Fenwick 树
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) bit.t[i][j] = 0;

        int p = 0;
        for (auto &mi : mid_id) {
            int m = mi.first, idx = mi.second;
            // 将所有数值 <= m 的单元格在 Fenwick 树中标记为 1
            while (p < (int)cells.size() && cells[p].v <= m) {
                bit.update(cells[p].x, cells[p].y, 1);
                p++;
            }
            // 查询当前子矩形内标记数（即 <= m 的数的个数）
            auto &qq = Q[idx];
            int cnt = bit.rect(qq.x1, qq.y1, qq.x2, qq.y2);

            // 根据 cnt 与 k 比较，调整上下界
            if (cnt >= qq.k)
                hi[idx] = m;
            else
                lo[idx] = m + 1;
        }
    }

    // 输出每个查询的最终答案 lo[i]
    for (int i = 0; i < q; i++) cout << lo[i] << "\n";

    return 0;
}