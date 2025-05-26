#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;

void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti;
// ...existing code...
void work() {
    string res;
    // 1) build a zero in r2
    cout << "/ r0 a a\n";
    cout.flush();  // r0 = a/a = 1
    cin >> res;
    cout << "/ r2 r0 a\n";
    cout.flush();  // r2 = r0/a = 0
    cin >> res;

    while (true) {
        // 2) q1 = a/b, q2 = c/d
        cout << "/ r0 a b\n";
        cout.flush();
        cin >> res;
        cout << "/ r1 c d\n";
        cout.flush();
        cin >> res;

        // 3) compare q1 vs q2
        cout << "? r0 r1\n";
        cout.flush();
        cin >> res;
        if (res == "<" || res == ">") {
            cout << "! " << res << "\n";
            cout.flush();
            return;
        }

        // 4) a -= q1*b, c -= q2*d
        cout << "* r3 r0 b\n";
        cout.flush();
        cin >> res;
        cout << "- a a r3\n";
        cout.flush();
        cin >> res;
        cout << "* r3 r1 d\n";
        cout.flush();
        cin >> res;
        cout << "- c c r3\n";
        cout.flush();
        cin >> res;

        // 5) if either remainder is zero, decide
        cout << "? a r2\n";
        cout.flush();
        cin >> res;
        if (res == "=") {
            cout << "? c r2\n";
            cout.flush();
            cin >> res;
            if (res == "=")
                cout << "! =\n";
            else
                cout << "! <\n";
            cout.flush();
            return;
        }
        cout << "? c r2\n";
        cout.flush();
        cin >> res;
        if (res == "=") {
            cout << "! >\n";
            cout.flush();
            return;
        }

        // 6) swap (a,b) <-> (d,c)
        //    use r3 as temp
        cout << "+ r3 r2 r2\n";
        cout.flush();
        cin >> res;  // r3 = 0
        cout << "+ r3 r3 a\n";
        cout.flush();
        cin >> res;  // r3 = a_old
        cout << "+ a r2 b\n";
        cout.flush();
        cin >> res;  // a = b_old
        cout << "+ b r2 r3\n";
        cout.flush();
        cin >> res;  // b = a_old

        cout << "+ r3 r2 c\n";
        cout.flush();
        cin >> res;  // r3 = c_old
        cout << "+ c r2 d\n";
        cout.flush();
        cin >> res;  // c = d_old
        cout << "+ d r2 r3\n";
        cout.flush();
        cin >> res;  // d = c_old
    }
}
// ...existing code...

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    if (ti == 0)
        cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}