#include<bits/stdc++.h>

using namespace std;
using ll = long long;

using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti;

void work() {
    int n, k;
    ll x;
    cin >> n >> k >> x;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> A(n + 1, 0);
    for (int i = 0; i < n; i++) {
        A[i + 1] = A[i] + a[i];
    }
    ll S = A[n];
    ll ans = 0;
    for (int j = 0; j < n; j++) {
        ll rem = k * S - x - A[j];
        if (rem < 0) continue;
        ll cnt = rem / S + 1;
        if (cnt > k) cnt = k;
        ans += cnt;
    }
    cout << ans << "\n";
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