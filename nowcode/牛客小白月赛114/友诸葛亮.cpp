#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;
using namespace numbers;

void be(int u, int v, auto e[N]) {
    cin >> u >> v;
    e[u].pb(v), e[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;

void work() {
    int x, y, z;
    cin >> x >> y >> z;
    int n = x + y + z;
    vector<int> pred(n);
    for (int i = 0; i < n; i++) {
        cin >> pred[i];
    }

    vector<vector<int>> gp(4);
    for (int i = 0; i < n; i++) {
        gp[pred[i]].push_back(i);
    }

    vector<int> c = {0, x, y, z};

    vector<int> forced(4, 0);
    for (int j = 1; j <= 3; j++) {
        forced[j] = max(0LL, 2LL * c[j] - n);
    }

    vector<int> ans(n, 0);
    vector<bool> ud(n, false);

    for (int j = 1; j <= 3; j++) {
        int cnt = forced[j];
        for (int idx = 0; idx < cnt && idx < gp[j].size(); idx++) {
            int pos = gp[j][idx];
            ans[pos] = j;
            ud[pos] = true;
        }
    }

    vector<int> L(4), A(4);
    for (int j = 1; j <= 3; j++) {
        L[j] = c[j] - forced[j];
        A[j] = gp[j].size() - forced[j];
    }

    int lower = max({0LL, L[2] - L[1], L[3] - L[1]});
    int upper = min({L[2], L[3], L[2] + L[3] - L[1]});
    int t = lower;
    int x12 = L[2] - t;
    int x13 = L[1] - x12;
    int x32 = t;
    int x31 = L[3] - t;
    int x21 = L[1] - x31;

    {
        int cnt = 0;
        for (int pos : gp[1]) {
            if (ud[pos]) continue;
            if (cnt < x12) {
                ans[pos] = 2;
            } else {
                ans[pos] = 3;
            }
            cnt++;
        }
    }
    {
        int cnt = 0;
        for (int pos : gp[2]) {
            if (ud[pos]) continue;
            if (cnt < x21) {
                ans[pos] = 1;
            } else {
                ans[pos] = 3;
            }
            cnt++;
        }
    }
    {
        int cnt = 0;
        for (int pos : gp[3]) {
            if (ud[pos]) continue;
            if (cnt < x31) {
                ans[pos] = 1;
            } else {
                ans[pos] = 2;
            }
            cnt++;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}