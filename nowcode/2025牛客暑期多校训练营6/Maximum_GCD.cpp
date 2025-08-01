#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

vector<vector<int>> build_sparse_table(const vector<int>& arr) {
    int n = arr.size();
    int max_log = log2(n) + 1;
    vector<vector<int>> st(max_log, vector<int>(n));
    st[0] = arr;
    for (int j = 1; j < max_log; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[j][i] = gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    return st;
}

int query_gcd(const vector<vector<int>>& st, int l, int r) {
    if (l > r) return 0;
    int j = log2(r - l + 1);
    return gcd(st[j][l], st[j][r - (1 << j) + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;

        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }

        // 差分数组
        vector<int> b(n - 1);
        for (int i = 1; i < n; ++i) b[i - 1] = abs(a[i] - a[i - 1]);

        // 构建 sparse table
        vector<vector<int>> st = build_sparse_table(b);

        // 前后缀 GCD
        vector<int> pre(n), suf(n);
        pre[0] = a[0];
        for (int i = 1; i < n; ++i) pre[i] = gcd(pre[i - 1], a[i]);
        suf[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i) suf[i] = gcd(a[i], suf[i + 1]);

        int ans = 0;

        // 差分区间枚举 + 二分
        for (int start = 0; start < n - 1; ++start) {
            int g0 = b[start];
            int low = start, high = n - 2, best = start;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (query_gcd(st, start, mid) == g0) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            int left = (start > 0) ? pre[start - 1] : 0;
            int right = (best + 2 < n) ? suf[best + 2] : 0;
            int total = gcd(g0, gcd(left, right));
            ans = max(ans, total);
        }

        // 额外考虑：单点加法
        for (int i = 0; i < n; ++i) {
            int g = 0;
            if (i > 0) g = gcd(g, pre[i - 1]);
            if (i + 1 < n) g = gcd(g, suf[i + 1]);
            g = gcd(g, a[i]);  // X = 0
            ans = max(ans, g);

            int g2 = 0;
            if (i > 0) g2 = gcd(g2, pre[i - 1]);
            if (i + 1 < n) g2 = gcd(g2, suf[i + 1]);
            ans = max(ans, g2);  // X = -a[i] → a[i] = 0
        }

        cout << ans << '\n';
    }

    return 0;
}
