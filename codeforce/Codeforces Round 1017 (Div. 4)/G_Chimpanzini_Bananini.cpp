// C++
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;

const int N = 2e6 + 5;

// Existing helper functions
void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].push_back(v), edges[u].push_back(v);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti;

void work() {
    int q;
    cin >> q;
    deque<int> dq;
    int S = 0, T = 0;
    bool rev = false;

    while (q--) {
        int s;
        cin >> s;
        int m = dq.size();
        if (s == 3) {
            int k;
            cin >> k;
            if (!rev) {
                dq.push_back(k);
            } else {
                dq.push_front(k);
            }
            m++;  // new size
            S += k * m;
            T += k;
            cout << S << "\n";
        } else if (s == 1) {
            int x;
            if (!rev) {
                x = dq.back();
                dq.pop_back();
                dq.push_front(x);
            } else {
                x = dq.front();
                dq.pop_front();
                dq.push_back(x);
            }
            S = S + T - m * x;
            cout << S << "\n";
        } else if (s == 2) {
            S = (m + 1) * T - S;
            rev = !rev;
            cout << S << "\n";
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