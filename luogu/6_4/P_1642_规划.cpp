#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using ld = long double;
const ld NEG_INF = -1e18;
const double eps = 1e-6;

int n, m;  // m 会被重置为要保留的节点数
int a[105], b[105];
vector<int> e[105];
ld f[105][105], val_[105];

void dfs(int u, int fa) {
    // 初始化：不选任何子节点
    rep(j, 0, m) f[u][j] = NEG_INF;
    f[u][0] = 0;
    // 合并每个子树
    for (int v : e[u])
        if (v != fa) {
            dfs(v, u);
            static ld tmp[105];
            rep(j, 0, m) tmp[j] = NEG_INF;
            rep(j, 0, m) if (f[u][j] > NEG_INF / 2) {
                rep(k, 0, m - j) if (f[v][k] > NEG_INF / 2) {
                    tmp[j + k] = max(tmp[j + k], f[u][j] + f[v][k]);
                }
            }
            rep(j, 0, m) f[u][j] = tmp[j];
        }
    // 选上 u 自己，占一个名额
    rem(j, m, 1) f[u][j] = f[u][j - 1] + val_[u];
    f[u][0] = 0;
}

bool check(ld R) {
    // 1) 计算每个节点的新权值
    rep(i, 1, n) val_[i] = a[i] - R * b[i];
    // 2) 一次 DFS，算出所有 f[u][0..m]
    dfs(1, 0);
    // 3) 枚举所有 u，看能否有 m 个点连通权值和 ≥ 0
    rep(u, 1, n) if (f[u][m] >= 0) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int remove_cnt;
    cin >> n >> remove_cnt;
    m = n - remove_cnt;  // 要保留的节点数
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> b[i];
    rep(i, 1, n) e[i].clear();
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    ld l = 0, r = 1e6, ans = 0;
    while (r - l > eps) {
        ld mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << fixed << setprecision(1) << ans << "\n";
    return 0;
}