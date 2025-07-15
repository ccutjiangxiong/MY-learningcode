#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define all(a) (a).begin(), (a).end()
#define low(a, x) lower_bound(all(a), x)
#define me(a, x) memset(a, x, sizeof(a))
using namespace std;
using pii = pair<int, int>;
using ll = long long;

const int N = 200000 + 5;
int ti = 1, n, m;
int a[N], b[N], cnt[N];
int sum;
int B;

struct Q {
    int l, r, id, ti;
    bool operator<(const Q &o) const {
        if (l / B != o.l / B) return l < o.l;
        if (r / B != o.r / B) return r < o.r;
        return ti < o.ti;
    }
} q[N];

pii h[N];
int t1, t2;

void add(int x) {
    if (!cnt[x]) sum++;
    cnt[x]++;
}
void del(int x) {
    cnt[x]--;
    if (!cnt[x]) sum--;
}

void work() {
    // reset
    t1 = t2 = sum = 0;
    me(cnt, 0);

    cin >> n >> m;
    vector<int> vs;
    vs.reserve(n + m + 5);

    rep(i, 1, n) {
        cin >> a[i];
        vs.push_back(a[i]);
    }
    // read ops
    rep(i, 1, m) {
        char ch;
        int l, r;
        cin >> ch >> l >> r;
        if (ch == 'Q') {
            ++t1;
            q[t1] = {l, r, t1, t2};
        } else {
            ++t2;
            h[t2] = {l, r};
            vs.push_back(r);
        }
    }
    // coordinate-compress
    sort(all(vs));
    vs.erase(unique(all(vs)), vs.end());
    rep(i, 1, n) a[i] = low(vs, a[i]) - vs.begin() + 1;
    rep(i, 1, t2) h[i].second = low(vs, h[i].second) - vs.begin() + 1;

    // Mo parameters
    B = max((int)pow(n, 2.0 / 3), 1);
    sort(q + 1, q + t1 + 1);

    // process queries
    for (int i = 1, l = 1, r = 0, t = 0; i <= t1; i++) {
        auto &Q = q[i];
        while (l > Q.l) add(a[--l]);
        while (r < Q.r) add(a[++r]);
        while (l < Q.l) del(a[l++]);
        while (r > Q.r) del(a[r--]);
        while (t < Q.ti) {
            int p = h[++t].first, v = h[t].second;
            if (l <= p && p <= r) {
                del(a[p]);
                add(v);
            }
            swap(a[p], h[t].second);
        }
        while (t > Q.ti) {
            int p = h[t].first, v = h[t].second;
            if (l <= p && p <= r) {
                del(a[p]);
                add(v);
            }
            swap(a[p], h[t--].second);
        }
        b[Q.id] = sum;
    }
    rep(i, 1, t1) { cout << b[i] << "\n"; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}