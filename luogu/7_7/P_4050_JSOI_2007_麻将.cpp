#include <bits/stdc++.h>
using namespace std;

// 判断剩余 3m 张牌能否全部组成刻子或顺子
bool canMelds(vector<int> tmp, int n) {
    for (int i = 1; i <= n; i++) {
        if (tmp[i] < 0) return false;
        int r = tmp[i] % 3;
        if (r) {
            // 需要 r 个顺子：i, i+1, i+2
            if (i + 2 > n) return false;
            tmp[i] -= r;
            tmp[i + 1] -= r;
            tmp[i + 2] -= r;
            if (tmp[i + 1] < 0 || tmp[i + 2] < 0) return false;
        }
    }
    return true;
}

// 判断加上一张牌后是否能和牌
bool isWinning(const vector<int>& cnt, int n) {
    // 枚举对子所在的牌面
    for (int i = 1; i <= n; i++) {
        if (cnt[i] >= 2) {
            vector<int> tmp = cnt;
            tmp[i] -= 2;
            if (canMelds(tmp, n)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> cnt(n + 3, 0);
    for (int i = 0, x; i < 3 * m + 1; i++) {
        cin >> x;
        cnt[x]++;
    }

    vector<int> waits;
    for (int x = 1; x <= n; x++) {
        cnt[x]++;
        if (isWinning(cnt, n)) waits.push_back(x);
        cnt[x]--;
    }

    if (waits.empty()) {
        cout << "NO";
    } else {
        for (int i = 0; i < waits.size(); i++) {
            if (i) cout << ' ';
            cout << waits[i];
        }
    }
    return 0;
}