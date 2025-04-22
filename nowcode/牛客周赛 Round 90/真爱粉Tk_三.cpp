#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define se second
#define fr first
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;

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

int ti = 1;

void work() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> t2(n), t5(n), ins(n);
    for (int i = 0; i < n; i++) {
        string s = to_string(a[i]);
        int cnt2 = 0, in = 0;
        for (char c : s) {
            if (c == '2')
                cnt2++;
            else if (c == '5')
                in += cnt2;
        }
        ins[i] = in;
        t2[i] = count(s.begin(), s.end(), '2');
        t5[i] = count(s.begin(), s.end(), '5');
    }
    auto can = [&](int mid) {
        int used = 1;
        int curr2 = 0, c = 0;
        for (int i = 0; i < n; i++) {
            int u = ins[i];
            if (u > mid) return false;  
            int cc = curr2 * t5[i];
            if (c + u + cc <= mid) {
                c += u + cc;
                curr2 += t2[i];
            } else {
                used++;
                c = u; 
                curr2 = t2[i];
            }
        }
        return used <= k;
    };


    int low = 0, high = 0, acc2 = 0;
    for (int i = 0; i < n; i++) {
        high += ins[i] + acc2 * t5[i];
        acc2 += t2[i];
    }


    while (low < high) {
        int mid = (low + high) >> 1;
        if (can(mid))
            high = mid;
        else
            low = mid + 1;
    }
    cout << low << "\n";
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