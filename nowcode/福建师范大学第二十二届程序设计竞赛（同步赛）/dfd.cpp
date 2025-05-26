#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define rem(i, a, b) for (int i = (a); i >= (b); --i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define cnt1(a) __builtin_popcountll(a)
#define cnt0(a) __builtin_clzll(a)
#define odd1(a) __builtin_parityll(a)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll d;
    cin >> n >> m >> d;
    vector<int> a(m), t(m);
    vector<ll> b(m);
    rep(i, 0, m - 1) { cin >> a[i] >> b[i] >> t[i]; }

    vector<ll> dp(n + 1, -INF), ndp(n + 1, -INF);
    dp[1] = b[0] * ll(abs(1 - a[0]));
    dp[n] = b[0] * ll(abs(n - a[0]));
    ll prev_t = t[0];

    rep(i, 1, m - 1) {
        ll delta = ll(t[i] - prev_t) * d;
        prev_t = t[i];
        ll win = min<ll>(delta, n);

        deque<int> dq;
        int r = 0;
        rep(j, 1, n) {
            int nr = min<ll>(n, j + win);
            while (r < nr) {
                ++r;
                while (!dq.empty() && dp[dq.back()] <= dp[r]) dq.pop_back();
                dq.pb(r);
            }
            int l = max<ll>(1, j - win);
            while (!dq.empty() && dq.front() < l) dq.pop_front();
            ndp[j] = dp[dq.front()] + b[i] * ll(abs(j - a[i]));
        }
        dp.swap(ndp);
        fill(all(ndp), -INF);
    }

    ll ans = *max_element(all(dp));
    cout << ans << "\n";
    return 0;
}