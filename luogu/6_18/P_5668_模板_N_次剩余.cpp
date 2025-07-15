#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 快速幂取模
inline ll mpow(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    while (e) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}
// 整数快速幂（不取模）
inline ll ipow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

// 扩展欧几里得：求 a·x + b·y = gcd(a, b)
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

// 求 n 次剩余：解 x^n ≡ k (mod m)
vector<ll> nth_root(ll n, ll m, ll k) {
    if (k == 0) return {0};

    // 分解 m = ∏ p^q
    vector<pair<ll, ll>> factors;
    ll t = m;
    for (ll p = 2; p * p <= t; ++p) {
        if (t % p == 0) {
            ll q = 0;
            while (t % p == 0) {
                t /= p;
                ++q;
            }
            factors.emplace_back(p, q);
        }
    }
    if (t > 1) factors.emplace_back(t, 1);

    vector<ll> all_sols;
    // 每个因子求在 p^q 下的解
    for (auto [p, q] : factors) {
        ll mod = ipow(p, q);
        ll phi = mod - 1;
        ll g = gcd(n, phi);
        if (mpow(k, phi / g, mod) != 1) return {};  // 无解

        ll n_g = n / g, phi_g = phi / g;
        ll u, v;
        exgcd(n_g, phi_g, u, v);
        u = (u % phi_g + phi_g) % phi_g;

        ll x0 = mpow(k, u, mod);
        ll omega = mpow(p, phi / g, mod);

        vector<ll> sols;
        for (ll i = 0; i < g; ++i) {
            sols.push_back((__int128)x0 * mpow(omega, i, mod) % mod);
        }
        sort(sols.begin(), sols.end());
        all_sols.insert(all_sols.end(), sols.begin(), sols.end());
    }

    // 中国剩余合并
    ll M = 1;
    for (auto [p, q] : factors) M *= ipow(p, q);

    vector<ll> result;
    for (ll x : all_sols) {
        ll res = 0;
        for (auto [p, q] : factors) {
            ll mod = ipow(p, q);
            ll Mi = M / mod;
            ll inv, tmp;
            exgcd(Mi, mod, inv, tmp);
            inv %= mod;
            if (inv < 0) inv += mod;
            res = (res + (__int128)x * Mi % M * inv) % M;
        }
        result.push_back((res + M) % M);
    }
    sort(result.begin(), result.end());
    return result;
}

void work() {
    int T;
    cin >> T;
    while (T--) {
        ll n, m, k;
        cin >> n >> m >> k;
        auto sols = nth_root(n, m, k);
        cout << sols.size() << "\n";
        if (!sols.empty()) {
            for (ll x : sols) cout << x << " ";
            cout << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    work();
    return 0;
}