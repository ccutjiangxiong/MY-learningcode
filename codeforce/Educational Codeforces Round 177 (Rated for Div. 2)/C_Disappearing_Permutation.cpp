#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;

void work() {
    int n;
    cin >> n;
    vector<int> p(n), d(n);
    rep(i, 0, n - 1) {
        cin >> p[i];
        p[i]--;  
    }
    rep(i, 0, n - 1) {
        cin >> d[i];
        d[i]--;  
    }

    vector<int> aa(n, -1);
    vector<int> cyl;
    int cid = 0;
    vector<bool> vi(n, false);
    rep(i, 0, n - 1) {
        if (!vi[i]) {
            int cur = i;
            vector<int> ccy;
            while (!vi[cur]) {
                vi[cur] = true;
                ccy.push_back(cur);
                cur = p[cur];
            }
            for (auto node : ccy) aa[node] = cid;
            cyl.push_back(ccy.size());
            cid++;
        }
    }

    vector<bool> in(cid, true);
    int sumin = n;  
    vector<int> ans;
    rep(i, 0, n - 1) {
        int pos = d[i];
        int id = aa[pos];
        if (in[id]) {
            in[id] = false;
            sumin -= cyl[id];
        }
        ans.push_back(n - sumin);
    }

    for (auto a : ans) cout << a << " ";
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