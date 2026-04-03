#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int N = 2e5 + 5;

struct H {
    int u, v, w;
    bool operator<(const H& other) const {
        return w < other.w;
    }
};

int pa[N], sz[N];

int find(int x) {
    if (pa[x] != x) {
        pa[x] = find(pa[x]);
    }
    return pa[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    pa[y] = x;
    sz[x] += sz[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<H> ed(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> ed[i].u >> ed[i].v >> ed[i].w;
    }

    sort(ed.begin(), ed.end());

    for (int i = 1; i <= n; i++) {
        pa[i] = i;
        sz[i] = 1;
    }

    ll ans = 0;
    for (auto& e : ed) {
        int ru = find(e.u), rv = find(e.v);
        ll su = sz[ru], sv = sz[rv];
        ll cont = (su % mod) * (sv % mod) % mod * (e.w % mod) % mod;
        ans = (ans + cont) % mod;
        unite(ru, rv);
    }

    cout << ans % mod << "\n";

    return 0;
}