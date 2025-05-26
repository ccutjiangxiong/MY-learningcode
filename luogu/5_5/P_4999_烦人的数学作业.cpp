#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>


#define INF 0x3f3f3f3f

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define lc u << 1
#define rc u << 1 | 1

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 ill;

const int N = 25;

ll t, l, r;
ll mod = 1e9 + 7;
ll f[30][10];

ll p10(int x) {
    ll ans = 1;
    while (x--) {
        ans = (ans * 10) % mod;
    }
    return ans;
}
void pre() {
    for (int i = 1; i <= N; i++) f[1][i] = i;
    for (int i = 2; i <= N; i++)
        for (int j = 0; j <= 9; j++) {
            f[i][j] = j * p10(i - 1);
            for (int k = 0; k <= 9; k++) f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
        }
}
ll dp(ll x) {
    ll y = x;
    ll ans = 0;
    int a[20];
    int cnt = 0;
    while (x) {
        a[++cnt] = x % 10, x /= 10;
    }
    for (int i = 1; i < cnt; i++)
        for (int j = 1; j <= 9; j++) ans = (ans + f[i][j]) % mod;
    int sum = 0;
    for (int i = cnt; i >= 1; i--) {
        ans = (ans + sum * a[i] * p10(i - 1)) % mod;
        for (int j = (i == cnt); j < a[i]; j++) {
            ans = (ans + f[i][j]) % mod;
        }
        sum += a[i];
    }

    return ans;
}

int main() {
    cin >> t;
    pre();
    while (t--) {
        cin >> l >> r;
        cout << ((dp(r + 1) + mod) - dp(l)) % mod << endl;
    }
}
