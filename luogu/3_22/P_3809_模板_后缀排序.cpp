#include <bits/stdc++.h>
// #include<iostream>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
// int df;
template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n, m = 222;
int x[N], y[N], c[N], sa[N], rk[N], h[N];
char s[N];
void Sa() {
    rep(i, 1, n) c[x[i] = s[i]]++;
    rep(i, 1, m) c[i] += c[i - 1];
    rem(i, n, 1) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        memset(c, 0, sizeof(c));
        rep(i, 1, n) y[i] = sa[i];
        rep(i, 1, n) c[x[y[i] + k]]++;
        rep(i, 1, m) c[i] += c[i - 1];
        rem(i, n, 1) sa[c[x[y[i] + k]]--] = y[i];
        memset(c, 0, sizeof(c));
        rep(i, 1, n) y[i] = sa[i];
        rep(i, 1, n) c[x[y[i]]]++;
        rep(i, 1, m) c[i] += c[i - 1];
        rem(i, n, 1) sa[c[x[y[i]]]--] = y[i];
        rep(i, 1, n) y[i] = x[i];
        m = 0;
        for (int i = 1; i <= n; i++)
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = m;
            else
                x[sa[i]] = ++m;
        if (m == n) break;
    }
    rep(i, 1, n) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 1) continue;
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        h[rk[i]] = k;
    }
}
void work() {
    cin >> (s + 1);
    n = strlen(s + 1);
    Sa();
    rep(i, 1, n) cout << sa[i] << ' ';
    rep(i, 2, n) print(h[i]);
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