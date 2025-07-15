
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
const int N = 1e6;
int ti;
vi e[N], ans;
int n, m;
vi st, aans;
int cnt[N];
set<int> s;
void dfs(int u) {
    if (cnt[u]++) {
        int res = 1, mi = u;
        rem(i, (int)(st.size()) - 1, 0) {
            res++;
            mi = min(u, st[i]);
            st.push_back(v);
        }
        if (!s.contains(mi)) s.insert(mi), aans.push_back(res);
    }
    st.push_back(v);
    for (int v : e[u]) {
        if (!cnt[v]) {
            dfs(v, u);
        }
    }
    st.pop_back();
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) e[i].clear();
    s.clear();
    rep(i, 1, n) cnt[i] = 0;

    rep(i, 1, m) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    rep(i, 1, n) if (!cnt[i]) st.push_back(i), dfs(i, 0);
    sort(aans.begin(), aans.end());
    cout << aans.size() << endl;
    // cout << aans.back() << aans[(int)(aans.size()) - 2] << endl;
    aans.clear();
}
signed main() {
    if (ti == 0) cin >> ti;
    while (ti--) work();
}