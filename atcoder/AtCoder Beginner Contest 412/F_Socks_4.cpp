#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
using ll = long long;

// fast exponentiation to compute modular inverse
ll modpow(ll a, ll e = MOD - 2) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, C;
    cin >> N >> C;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    // total socks mod MOD
    ll T = 0;
    for (ll x : A) T = (T + x) % MOD;

    // sort colors by A[i], keep original indices
    vector<pair<ll, int>> v(N);
    for (int i = 0; i < N; i++) v[i] = {A[i], i};
    sort(v.begin(), v.end(), [&](auto &l, auto &r) {
        if (l.first != r.first) return l.first < r.first;
        return l.second < r.second;
    });

    vector<ll> E_orig(N);
    ll suffixSum = 0, suffixWeightedE = 0;
    // process in descending order of A[i]
    for (int i = N - 1; i >= 0; i--) {
        ll Ai = v[i].first % MOD;
        int idx = v[i].second;
        // E[i] = (T + sum_{j: Aj>Ai} Aj * E[j]) / (suffixSum + Ai)
        ll numer = (T + suffixWeightedE) % MOD;
        ll denom = (suffixSum + Ai) % MOD;
        ll Ei = numer * modpow(denom) % MOD;
        E_orig[idx] = Ei;
        suffixSum = (suffixSum + Ai) % MOD;
        suffixWeightedE = (suffixWeightedE + Ai * Ei) % MOD;
    }

    // output E[C]
    cout << E_orig[C - 1] << "\n";
    return 0;
}