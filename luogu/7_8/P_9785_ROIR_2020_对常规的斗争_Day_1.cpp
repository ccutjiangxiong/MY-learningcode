#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // prev occurrence
    unordered_map<int, int> last;
    vector<int> prev(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prev[i] = last.count(a[i]) ? last[a[i]] : 0;
        last[a[i]] = i;
    }

    // diff arrays for coeff[d] * d + const_[d]
    vector<ll> dC(n + 2, 0), dK(n + 2, 0);

    for (int i = 1; i <= n; i++) {
        int p = prev[i];
        int x = i - p;
        int y = n - i + 1;
        int u = min(x, y), v = max(x, y);
        int C = n - p + 1;
        int end = C - 1;  // max d

        // 1) [1..u]: +1 * d
        if (u >= 1) {
            dC[1] += 1;
            dC[u + 1] -= 1;
        }
        // 2) [u+1..v]: +u
        if (v >= u + 1) {
            dK[u + 1] += u;
            dK[v + 1] -= u;
        }
        // 3) [v+1..end]: -1 * d + C
        if (end >= v + 1) {
            dC[v + 1] -= 1;
            dC[end + 1] += 1;
            dK[v + 1] += C;
            dK[end + 1] -= C;
        }
    }

    // recover coeff and const_, then S[d]
    vector<ll> S(n + 1, 0);
    ll curC = 0, curK = 0;
    for (int d = 1; d <= n; d++) {
        curC += dC[d];
        curK += dK[d];
        S[d] = curC * d + curK;
    }

    // output
    for (int d = 1; d <= n; d++) {
        cout << S[d] << (d < n ? ' ' : '\n');
    }
    return 0;
}