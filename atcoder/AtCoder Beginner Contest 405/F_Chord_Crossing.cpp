#include <bits/stdc++.h>
using namespace std;
#define int long long
struct BIT {
    int N;
    vector<int> t;
    BIT(int _N = 0) : N(_N), t(N + 1, 0) {}
    void add(int i, int v = 1) {
        for (; i <= N; i += i & -i) t[i] += v;
    }
    int sum(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    int range_sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

void work() {
    int N, M;
    cin >> N >> M;
    int P = 2 * N;
    vector<pair<int, int>> segs(M);
    BIT asdja(P);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        segs[i] = {a, b};
        asdja.add(a);
        asdja.add(b);
    }

    int Q;
    cin >> Q;
    struct Query {
        int X, Y, idx;
        bool wrap;
        int C, D;
    };
    vector<Query> qs;
    qs.reserve(Q);
    for (int i = 0; i < Q; i++) {
        int C, D;
        cin >> C >> D;
        if (C < D) {
            qs.push_back({C, D, i, false, C, D});
        } else {
            qs.push_back({D, C, i, true, C, D});
        }
    }

    sort(segs.begin(), segs.end(),
         [&](auto &A, auto &B) { return A.first > B.first; });
    vector<int> ord(Q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(),
         [&](int i, int j) { return qs[i].X > qs[j].X; });

    BIT bitR(P);
    vector<int> aa(Q, 0);
    int p = 0;
    for (int qi : ord) {
        int X = qs[qi].X, Y = qs[qi].Y;
        while (p < M && segs[p].first > X) {
            bitR.add(segs[p].second, 1);
            p++;
        }
        aa[qi] = bitR.range_sum(1, Y - 1);
    }

    vector<int> ans(Q);
    for (int i = 0; i < Q; i++) {
        auto &q = qs[i];
        int both = (!q.wrap ? aa[i] : M - aa[i]);
        int epi = 0;
        if (!q.wrap) {
            epi = asdja.range_sum(q.C + 1, q.D - 1);
        } else {
            epi = asdja.range_sum(q.C + 1, P) +
                  asdja.range_sum(1, q.D - 1);
        }
        ans[q.idx] = epi - 2 * both;
    }

    for (int x : ans) {
        cout << x << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    while (T--) work();
    return 0;
}