#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;

void work() {
    string s;
    cin >> s;
    int n = s.size();
    int cnt1 = 0;
    for (char c : s) cnt1 += (c == '1');
    int cand1 = n / 2;
    int cand2 = n - cand1;
    int target;
    if ((cand1 & 1) == (cnt1 & 1))
        target = cand1;
    else
        target = cand2;

    vector<int> d(n, 0);
    for (int i = n - target; i < n; i++) d[i] = 1;

    vector<int> op(n - 1, 0);
    int bit = (s[0] - '0') ^ d[0];
    op[0] = bit;
    for (int i = 1; i < n - 1; i++) {
        bit = op[i - 1] ^ ((s[i] - '0') ^ d[i]);
        op[i] = bit;
    }

    if (((s[n - 1] - '0') ^ op[n - 2]) != d[n - 1]) {
    }

    vector<int> ops;
    for (int i = 0; i < n - 1; i++) {
        if (op[i] == 1) ops.push_back(i + 1);
    }

    int zeros = n - target;
    int ones = target;
    cout << zeros * ones << "\n";
    cout << ops.size() << "\n";
    for (int i = 0; i < ops.size(); i++) {
        cout << ops[i] << (i + 1 < ops.size() ? " " : "\n");
    }
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