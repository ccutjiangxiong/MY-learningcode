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
#define sz(a) (int)a.size()
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

// ...existing code...

struct Node {
    Node *ch[2], *fa;
    bool rev;
    ll val, sum;
}* tr[N];

bool is_root(Node* x) { return !x->fa || (x->fa->ch[0] != x && x->fa->ch[1] != x); }
void push_up(Node* x) {
    x->sum = x->val ^ (x->ch[0] ? x->ch[0]->sum : 0) ^ (x->ch[1] ? x->ch[1]->sum : 0);
}
void push_down(Node* x) {
    if (!x->rev) return;
    swap(x->ch[0], x->ch[1]);
    for (auto c : {x->ch[0], x->ch[1]})
        if (c) c->rev ^= 1;
    x->rev = 0;
}
void rotate(Node* x) {
    Node* y = x->fa;
    Node* z = y->fa;
    bool dx = (y->ch[1] == x), dy = (z && z->ch[1] == y);
    if (!is_root(y)) z->ch[dy] = x;
    x->fa = z;
    y->ch[dx] = x->ch[!dx];
    if (x->ch[!dx]) x->ch[!dx]->fa = y;
    x->ch[!dx] = y;
    y->fa = x;
    push_up(y);
    push_up(x);
}
void push_all(Node* x) {
    if (!is_root(x)) push_all(x->fa);
    push_down(x);
}
void splay(Node* x) {
    push_all(x);
    while (!is_root(x)) {
        Node* y = x->fa;
        Node* z = y->fa;
        if (!is_root(y)) ((y->ch[0] == x) ^ (z->ch[0] == y)) ? rotate(x) : rotate(y);
        rotate(x);
    }
}
void access(Node* x) {
    for (Node* y = nullptr; x; y = x, x = x->fa) {
        splay(x);
        x->ch[1] = y;
        push_up(x);
    }
}
void makeroot(Node* x) {
    access(x);
    splay(x);
    x->rev ^= 1;
}
Node* findroot(Node* x) {
    access(x);
    splay(x);
    while (push_down(x), x->ch[0]) x = x->ch[0];
    splay(x);
    return x;
}
void split(Node* x, Node* y) {
    makeroot(x);
    access(y);
    splay(y);
}
void link(Node* x, Node* y) {
    makeroot(x);
    if (findroot(y) != x) x->fa = y;
}
void cut(Node* x, Node* y) {
    makeroot(x);
    if (findroot(y) == x && y->fa == x && !y->ch[0]) {
        y->fa = nullptr;
        x->ch[1] = nullptr;
        push_up(x);
    }
}
void work() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        tr[i] = new Node();
        cin >> tr[i]->val;
        tr[i]->sum = tr[i]->val;
    }
    int op, x, y;
    while (m--) {
        cin >> op >> x >> y;
        if (op == 0) {
            split(tr[x], tr[y]);
            cout << tr[y]->sum << "\n";
        } else if (op == 1) {
            link(tr[x], tr[y]);
        } else if (op == 2) {
            cut(tr[x], tr[y]);
        } else if (op == 3) {
            splay(tr[x]);
            tr[x]->val = y;
            push_up(tr[x]);
        }
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