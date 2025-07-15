#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)x.size()
template <typename T>
istream& operator>>(istream& in, vector<T>& a) {
    for (auto& x : a) in >> x;
    return in;
};

// 线段树节点
struct Node {
    int sum;   // 区间和
    int pref;  // 最大前缀和
    int suff;  // 最大后缀和
    int best;  // 最大子数组和
    Node() : sum(0), pref(0), suff(0), best(0) {}
    Node(int x) : sum(x), pref(max(0, x)), suff(max(0, x)), best(max(0, x)) {}
};

// 合并两个子节点
Node merge(const Node& L, const Node& R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.best = max({L.best, R.best, L.suff + R.pref});
    return res;
}

// 线段树
struct segtree {
    int n;
    vector<Node> st;
    segtree(int _n) {
        n = _n;
        st.resize(4 * n);
        build(1, 0, n - 1);
    }
    void build(int p, int l, int r) {
        if (l == r) {
            st[p] = Node(-1);
            return;
        }
        int m = (l + r) / 2;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = Node(val);
            return;
        }
        int m = (l + r) / 2;
        if (idx <= m)
            update(p << 1, l, m, idx, val);
        else
            update(p << 1 | 1, m + 1, r, idx, val);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    Node query(int p, int l, int r, int i, int j) {
        if (i > r || j < l) {
            Node nullnode;
            nullnode.sum = 0;
            nullnode.pref = nullnode.suff = nullnode.best = INT_MIN;
            return nullnode;
        }
        if (l >= i && r <= j) return st[p];
        int m = (l + r) / 2;
        Node L = query(p << 1, l, m, i, j);
        Node R = query(p << 1 | 1, m + 1, r, i, j);
        if (L.best == INT_MIN) return R;
        if (R.best == INT_MIN) return L;
        return merge(L, R);
    }
    int max_subarray() {
        Node res = query(1, 0, n - 1, 0, n - 1);
        return res.best;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    vector<vector<int>> at(n + 1);  // 记录每个值的初始位置
    FOR(i, 0, n) at[a[i]].pb(i);

    vector<vector<array<int, 3>>> updates(n + 1);  // 记录每个值的更新操作
    FOR(idx, 0, q) {
        int i, x;
        cin >> i >> x;
        --i;
        if (x != a[i]) {
            updates[a[i]].pb({idx, i, -1});  // 原值的更新
            a[i] = x;
            updates[x].pb({idx, i, 1});  // 新值的更新
        }
    }

    vector<vector<int>> final_at(n + 1);  // 记录最终每个值的位置
    FOR(i, 0, n) final_at[a[i]].pb(i);

    segtree st(n);                             // 初始化线段树
    vector<int> init(n + 1);                   // 记录每个值的初始最大子数组和
    vector<vector<pair<int, int>>> change(q);  // 记录每次查询对最大子数组和的改变

    // 处理每个值 x
    FOR(x, 1, n + 1) {
        // 初始化线段树：x 的位置为 1，其他为 -1
        trav(i, at[x]) st.update(i, 1);
        int cur = st.max_subarray();
        init[x] = cur;

        // 应用所有与 x 相关的更新
        trav(op, updates[x]) {
            st.update(op[1], op[2]);
            int new_cur = st.max_subarray();
            change[op[0]].pb({cur, new_cur});
            cur = new_cur;
        }

        // 恢复线段树初始状态
        trav(i, final_at[x]) st.update(i, -1);
    }

    multiset<int> ms;  // 维护所有 x 的当前最大子数组和
    FOR(i, 1, n + 1) ms.insert(init[i]);

    // 处理查询
    FOR(i, 0, q) {
        trav(p, change[i]) {
            ms.erase(ms.find(p.F));
            ms.insert(p.S);
        }
        cout << *prev(ms.end()) / 2 << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        solve();
    }
}