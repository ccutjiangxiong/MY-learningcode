#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e3 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n, a[N], pre[N];
int dp[N][2];
vector<int> get_ran(int x, int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, n);
    set<int> ss;
    while (ss.size() < x) ss.insert(dis(gen));
    vector<int> result(ss.begin(), ss.end());
    result.push_back(dis(gen));
    return result;
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
    int ans = inf;
    // print(a[1]);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, n);
    rep(i, 1, 2e6) {
        set<int> ss;
        while (ss.size() < 3) ss.insert(dis(gen));
        vector<int> st(ss.begin(), ss.end());
        st.push_back(dis(gen));
        // vector<int> st = get_ran(4, n);
        // for (int x : st) print(x);

        sort(st.begin(), st.end());

        // print(st[0], st[1], st[2] - 1, st[3]);
        ans = min(ans, abs(pre[st[3]] - pre[st[2]] - pre[st[1]] + pre[st[0]]));
    }
    cout << ans << endl;
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