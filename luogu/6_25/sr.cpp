#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int maxA = 0;
    for (int &x : a) {
        cin >> x;
        maxA = max(maxA, x);
    }

    // 1) 统计频次，记录单点最大
    unordered_map<int, int> freq;
    freq.reserve(n * 2);
    int ans = 0;
    for (int x : a) {
        int &f = freq[x];
        f++;
        ans = max(ans, f);
    }
    if (n <= 1 || ans == n) {
        cout << ans << "\n";
        return 0;
    }

    // 2) 筛素数到 maxA（只取到 L），L 可调
    const int L = 500;
    vector<bool> is_p(maxA + 1, true);
    vector<int> primes;
    is_p[0] = is_p[1] = false;
    for (int i = 2; i <= maxA; i++) {
        if (is_p[i]) {
            if ((int)primes.size() < L) primes.push_back(i);
            if ((ll)i * i <= maxA)
                for (int j = i * i; j <= maxA; j += i) is_p[j] = false;
        }
    }

    // 3) 对每个小素数 p 枚举残余类
    vector<pair<int, int>> vals;
    vals.reserve(freq.size());
    for (auto &kv : freq) {
        vals.emplace_back(kv.first, kv.second);
    }

    for (int p : primes) {
        if (ans >= (n + p - 1) / p) {
            // 当前 ans 已经 >= n/p，剩余更大的 p 不会有更优解
            break;
        }
        unordered_map<int, int> cnt;
        cnt.reserve(vals.size() * 2);
        int best = 0;
        for (auto &vi : vals) {
            int r = vi.first % p;
            int c = (++cnt[r]);
            if (c == 1)
                c = vi.second;  // 第一次要加上 freq[v]
            else
                c += vi.second;  // 后续累加
            best = max(best, c);
        }
        ans = max(ans, best);
    }

    cout << ans << "\n";
    return 0;
}