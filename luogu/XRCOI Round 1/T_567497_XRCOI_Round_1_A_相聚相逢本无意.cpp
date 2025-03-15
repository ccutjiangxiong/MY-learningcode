#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

int in() {
    int x;
    return (cin >> x, x);
}
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n;
int p[200];
vector<int> h;
int cnt = 0;
void work() {
    cin >> n;
    rep(i, 0, n) p[i] = -1;
    rep(i, 1, n) {
        // p[in()] = in();
        int u, v;
        cin >> u >> v;
        p[u] = v;
        cnt += v;
    };
    if (cnt == 0) {
        if (p[0] == 0 && p[1]) {
            print(1);
            print(0);
        } else if (p[1] == 0 && p[0]) {
            print(1);
            print(1);
        } else if (p[0] && p[1]) {
            print(1);
            print(0);
        } else {
            print(-1);
        }
        return;
    }
    if (p[0] == cnt) {
        print(cnt);
        rep(i, 1, cnt) cout << 1 << ' ';
        return;
    }
    if (p[0] > 0) {
        print(-1);
        return;
    };
    int cnt1 = 0;
    rep(i, 1, 111) {
        if (p[i] > 0) {
            rep(j, 1, p[i]) h.push_back(i - 1);
            cnt1 += p[i];
        };
        if (p[i] == 0 && cnt1 != cnt) {
            cout << -1 << endl;
            return;
        }
        if (p[i] == -1) h.push_back(i - 1);
    }
    print(h.size());
    for (int x : h) cout << x << ' ';
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