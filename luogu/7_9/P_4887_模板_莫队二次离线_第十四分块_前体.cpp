#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXV = 1 << 14;  // 值域上限
struct Query {
    int l, r, id;
};

int n, m, k;
int a[100000 + 5];
ll ans[100000 + 5];
int freqv[MAXV];
vector<int> diffs;

inline int popc(int x) { return __builtin_popcount(x); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // 预处理所有 popcount(d)==k 的 d
    for (int d = 0; d < MAXV; d++) {
        if (popc(d) == k) diffs.push_back(d);
    }

    vector<Query> qs(m);
    for (int i = 0; i < m; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
    }

    int B = max(1, int(sqrt(n)));
    sort(qs.begin(), qs.end(), [&](auto &A, auto &BQ) {
        int b1 = A.l / B, b2 = BQ.l / B;
        if (b1 != b2) return b1 < b2;
        return A.r < BQ.r;
    });

    int curL = 1, curR = 0;
    ll curAns = 0;
    auto add = [&](int pos) {
        int x = a[pos];
        // 新增 x，与窗口里所有 y，popcount(x^y)==k 的对数
        for (int d : diffs) {
            int y = x ^ d;
            if (y < MAXV) curAns += freqv[y];
        }
        freqv[x]++;
    };
    auto remove = [&](int pos) {
        int x = a[pos];
        freqv[x]--;
        for (int d : diffs) {
            int y = x ^ d;
            if (y < MAXV) curAns -= freqv[y];
        }
    };

    for (auto &q : qs) {
        int L = q.l, R = q.r;
        while (curL > L) add(--curL);
        while (curR < R) add(++curR);
        while (curL < L) remove(curL++);
        while (curR > R) remove(curR--);
        ans[q.id] = curAns;
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}