#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

namespace Milkcat {
typedef long long LL;
typedef pair<LL, LL> pii;
// 最大状态数：n*(状态维度18)+……
const int N = 4e6 + 5;

int n, k, x;
// a[i] = 手牌中点数为 i 的牌的数量
int a[N];
// vis[i] 标记点数 i 是否可“听”
int vis[N];
// g[i][j][k][p] 表示：已处理点数到 i，
//   j = 上一张牌留到下一个 i+1 做顺子的数量 (0~2)
//   k = 当前牌剩余去 3 后的余数 (0~2)
//   p = 是否已用雀头 (0/1)
//   若状态可达则 =1
int g[N][3][3][2];

// 状态反向图：从下一个状态指回上一个状态
vector<int> G[N];
// C[u] 存放：从状态 u 听的所有点数
vector<int> C[N];
vector<int> res;

// 将 (i,j,k,p) 映射到唯一 id
inline int id(int i, int j, int k, int p) { return i * 18 + j * 6 + k * 2 + p; }

// 从终态向前 DFS，标记所有可“听”点数
void dfs(int u) {
    for (int v : C[u]) {
        vis[v] = 1;
    }
    for (int v : G[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 输入 n (牌种类), k (手牌数)
    cin >> n >> k;
    // 统计每种牌的数量
    for (int i = 1; i <= k; i++) {
        cin >> x;
        a[x]++;
    }

    // 初始状态：i=0, j=0, k=0, p=0
    g[0][0][0][0] = 1;

    // 枚举点数从 0 过渡到 n
    for (int i = 0; i < n; i++) {
        // 填 DP 状态 g
        for (int j = 0; j < 3; j++) {
            for (int k2 = 0; k2 < 3; k2++) {
                for (int p = 0; p < 2; p++) {
                    if (!g[i][j][k2][p]) continue;
                    int cnt = a[i + 1];
                    // 不做雀头：用 j + k2 去搭面子，剩余 %3
                    if (cnt >= j + k2) {
                        g[i + 1][k2][(cnt - j - k2) % 3][p] = 1;
                    }
                    // 做雀头（未用过 p==0 且至少多 2 张）
                    if (!p && cnt >= j + k2 + 2) {
                        g[i + 1][k2][(cnt - j - k2 - 2) % 3][1] = 1;
                    }
                }
            }
        }

        // 构建反向边 G：从后继状态指回当前状态 id(i,j,k2,p)
        for (int j = 0; j < 3; j++) {
            for (int k2 = 0; k2 < 3; k2++) {
                for (int p = 0; p < 2; p++) {
                    int cur = id(i, j, k2, p);
                    int cnt = a[i + 1];
                    if (cnt >= j + k2) {
                        int nxt = id(i + 1, k2, (cnt - j - k2) % 3, p);
                        G[nxt].push_back(cur);
                    }
                    if (!p && cnt >= j + k2 + 2) {
                        int nxt = id(i + 1, k2, (cnt - j - k2 - 2) % 3, 1);
                        G[nxt].push_back(cur);
                    }
                }
            }
        }

        // 模拟“听”这张牌：在原 cnt 基础上 +1
        a[i + 1]++;
        // 对所有可达状态，记录 C[next] 可听点数 i+1
        for (int j = 0; j < 3; j++) {
            for (int k2 = 0; k2 < 3; k2++) {
                for (int p = 0; p < 2; p++) {
                    if (!g[i][j][k2][p]) continue;
                    int cnt = a[i + 1];
                    if (cnt >= j + k2) {
                        int nxt = id(i + 1, k2, (cnt - j - k2) % 3, p);
                        C[nxt].push_back(i + 1);
                    }
                    if (!p && cnt >= j + k2 + 2) {
                        int nxt = id(i + 1, k2, (cnt - j - k2 - 2) % 3, 1);
                        C[nxt].push_back(i + 1);
                    }
                }
            }
        }
    }

    // 从最终“和牌”状态 (n,0,0,1) 开始 DFS
    dfs(id(n, 0, 0, 1));

    // 收集所有 vis[i]=1 的点数
    for (int i = 1; i <= n; i++) {
        if (vis[i]) res.push_back(i);
    }
    // 若无结果，输出 QAQ
    if (res.empty()) {
        cout << "QAQ\n";
    } else {
        for (int v : res) cout << v << ' ';
        cout << '\n';
    }

    return 0;
}
}  // namespace Milkcat

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Milkcat::main();
    return 0;
}