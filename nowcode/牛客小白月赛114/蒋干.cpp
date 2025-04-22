#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;
// using namespace numbers;
void be(int u, int v, auto e[N]) {
    cin >> u >> v;
    e[u].pb(v), e[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;
int n, m, k;
map<string, map<string, int>> mp, mp2;
set<string> mpp;
set<string> hp, hp2, hp3;
void work() {
    cin >> n >> m >> k;
    rep(i, 1, n) {
        string s, t;
        cin >> s >> t;
        mp[t][s]++;
        hp3.insert(s);
    }
    rep(i, 1, m) {
        string s, t;
        cin >> s >> t;
        mp2[t][s]++;
        hp.insert(t);
        hp2.insert(s);
    }
    rep(i, 1, k) {
        string s;
        cin >> s;
        if (hp3.find(s) != hp3.end()) mpp.insert(s);
    }
    bool ans = false;
    for (auto s : mp2) {
        for (auto t : s.second) {
            for (auto ss : mpp) {
                string &x = ss;
                if (x != t.first && mp[s.first][x] > mp2[s.first][x]) {
                    if (mp2[s.first][x]) {
                        if (mp2[s.first][t.first] == 1 && hp.size() == 2) continue;
                        if (mp2[s.first][t.first] == 1 && hp2.size() == 2) continue;
                    }
                    print("Yes");
                    print(t.first, s.first);
                    print(x, s.first);
                    return;
                }
                if (x == t.first && (hp.size() != 1 || hp2.size() != 1)) {
                    print("Yes");
                    print(x, s.first);
                    print(x, s.first);
                    return;
                }
            }
        }
    }
    cout << "No" << endl;
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