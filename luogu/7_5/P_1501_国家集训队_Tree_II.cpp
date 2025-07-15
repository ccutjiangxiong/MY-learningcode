#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define allp(a) a->begin(), a->end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
// #define sz(a) (int)a.size()
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define low lower_bound
#define upp upper_bound
#define con contains
#define me(a, x) memset(a, x, sizeof(a))
#define pta(x, a, b) rep(i, a, b) cout << x[i] << " \n"[i == b];
#define me1(x, n, ...) \
    for (auto* h : {__VA_ARGS__}) rep(i, 0, (n)) h[i] = x;
#define me2(x, n, m, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, 0, (n)) rep(j, 0, (m)) h[i][j] = x;
#define fi1(x, n1, n2, ...) \
    for (auto* h : {__VA_ARGS__}) rep(i, (n1), (n2)) h[i] = x;
#define fl2(x, n1, n2, m1, m2, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, (n1), (n2)) rep(j, (m1), (m2)) h[i][j] = x;
#define Ye(x) (x) ? "YES" : "NO"
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename Compare = std::greater<T>>
using hp = __gnu_pbds::priority_queue<T, Compare, pairing_heap_tag>;
template <typename Key, typename Mapped = null_type, typename Access = trie_string_access_traits<>>
using tri = trie<Key, Mapped, Access, pat_trie_tag, trie_prefix_search_node_update>;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;
using ll = int64_t;
using cpx = complex<ld>;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f1[N], f2[N], g1[N], g2[N];
vi e[N];

// ...existing code above...
const int MOD = 51061;
struct Node {
    Node *ch[2], *fa;
    bool rev;
    ll v, sum, add, mul;
    int sz;
};
Node* tr[N];
bool isRoot(Node* x) { return !x->fa || (x->fa->ch[0] != x && x->fa->ch[1] != x); }
void pushUp(Node* x) {
    x->sz = 1;
    x->sum = x->v % MOD;
    if (x->ch[0]) {
        x->sz += x->ch[0]->sz;
        x->sum = (x->sum + x->ch[0]->sum) % MOD;
    }
    if (x->ch[1]) {
        x->sz += x->ch[1]->sz;
        x->sum = (x->sum + x->ch[1]->sum) % MOD;
    }
}
void applyMul(Node* x, ll c) {
    x->v = x->v * c % MOD;
    x->sum = x->sum * c % MOD;
    x->mul = x->mul * c % MOD;
    x->add = x->add * c % MOD;
}
void applyAdd(Node* x, ll c) {
    x->v = (x->v + c) % MOD;
    x->sum = (x->sum + c * x->sz) % MOD;
    x->add = (x->add + c) % MOD;
}
void pushDown(Node* x) {
    if (x->rev) {
        swap(x->ch[0], x->ch[1]);
        if (x->ch[0]) x->ch[0]->rev ^= 1;
        if (x->ch[1]) x->ch[1]->rev ^= 1;
        x->rev = false;
    }
    if (x->mul != 1) {
        if (x->ch[0]) applyMul(x->ch[0], x->mul);
        if (x->ch[1]) applyMul(x->ch[1], x->mul);
        x->mul = 1;
    }
    if (x->add != 0) {
        if (x->ch[0]) applyAdd(x->ch[0], x->add);
        if (x->ch[1]) applyAdd(x->ch[1], x->add);
        x->add = 0;
    }
}
void rotate(Node* x) {
    Node *p = x->fa, *g = p->fa;
    int dir = (p->ch[1] == x);
    if (!isRoot(p)) g->ch[g->ch[1] == p] = x;
    x->fa = g;
    p->ch[dir] = x->ch[dir ^ 1];
    if (x->ch[dir ^ 1]) x->ch[dir ^ 1]->fa = p;
    x->ch[dir ^ 1] = p;
    p->fa = x;
    pushUp(p);
    pushUp(x);
}
void pushAll(Node* x) {
    if (!isRoot(x)) pushAll(x->fa);
    pushDown(x);
}
void splay(Node* x) {
    pushAll(x);
    while (!isRoot(x)) {
        Node* p = x->fa;
        Node* g = p->fa;
        if (!isRoot(p)) {
            if ((p->ch[0] == x) ^ (g->ch[0] == p))
                rotate(x);
            else
                rotate(p);
        }
        rotate(x);
    }
}
void access(Node* x) {
    Node* last = nullptr;
    for (Node* y = x; y; y = y->fa) {
        splay(y);
        y->ch[1] = last;
        pushUp(y);
        last = y;
    }
    splay(x);
}
void makeRoot(Node* x) {
    access(x);
    x->rev ^= 1;
}
Node* findRoot(Node* x) {
    access(x);
    while (true) {
        pushDown(x);
        if (!x->ch[0]) break;
        x = x->ch[0];
    }
    splay(x);
    return x;
}
void split(Node* x, Node* y) {
    makeRoot(x);
    access(y);
}
void link(Node* x, Node* y) {
    makeRoot(x);
    if (findRoot(y) != x) x->fa = y;
}
void cut(Node* x, Node* y) {
    split(x, y);
    if (y->ch[0] == x) {
        y->ch[0]->fa = nullptr;
        y->ch[0] = nullptr;
    }
    pushUp(y);
}
void work() {
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        tr[i] = new Node();
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        link(tr[u], tr[v]);
    }
    while (q--) {
        char op;
        cin >> op;
        if (op == '+') {
            int u, v;
            ll c;
            cin >> u >> v >> c;
            split(tr[u], tr[v]);
            applyAdd(tr[v], c);
        } else if (op == '*') {
            int u, v;
            ll c;
            cin >> u >> v >> c;
            split(tr[u], tr[v]);
            applyMul(tr[v], c);
        } else if (op == '-') {
            int u1, v1, u2, v2;
            cin >> u1 >> v1 >> u2 >> v2;
            cut(tr[u1], tr[v1]);
            link(tr[u2], tr[v2]);
        } else if (op == '/') {
            int u, v;
            cin >> u >> v;
            split(tr[u], tr[v]);
            cout << (tr[v]->sum % MOD + MOD) % MOD << "\n";
        }
    }
}
// ...existing code below...
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}