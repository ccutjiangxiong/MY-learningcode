#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;  // s 的长度为 n

    // 构造 cnt 矩阵：cnt[x][y] 表示 s 中某位置字母 x，其右侧出现字母 y 的次数
    vector<vector<long long>> cnt(26, vector<long long>(26, 0));
    vector<int> freq(26, 0);
    // 从右向左遍历 s，统计后缀频次
    for (int i = n - 1; i >= 0; i--) {
        int x = s[i] - 'a';
        // 对于出现的每个其他字母 y，累加其频次
        for (int y = 0; y < 26; y++) {
            if (y == x) continue;
            cnt[x][y] += freq[y];
        }
        freq[x]++;
    }

    // 对每个平行宇宙，计算逆序对数量
    for (int qi = 0; qi < q; qi++) {
        string order;  // 当前宇宙的字母表排列
        cin >> order;
        // 构造 pos 数组，记录每个字母在当前排列中的位置
        // 例如 pos['a'-'a'] = 下标，数字越小意味字母越“轻”
        vector<int> pos(26, 0);
        for (int i = 0; i < 26; i++) {
            pos[order[i] - 'a'] = i;
        }
        long long ans = 0;
        // 枚举所有字母对 (x, y)
        for (int x = 0; x < 26; x++) {
            for (int y = 0; y < 26; y++) {
                // 如果在当前宇宙中字母 x 的顺序在字母 y 之后，
                // 那么所有 s 中 x 在 y 前的贡献都构成逆序对
                if (pos[x] > pos[y]) ans += cnt[x][y];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}