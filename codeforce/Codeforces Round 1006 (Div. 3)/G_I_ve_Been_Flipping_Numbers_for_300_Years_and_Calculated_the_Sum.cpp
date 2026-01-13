#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
typedef long long ll;
const ll mod = 1e9 + 7;
int n;
ll k, ans;
ll psquared[N];
void init() {
    for (int i = 1; i < N; i++) {
        psquared[i] = (psquared[i - 1] + ll(i) * i) % mod;
    }
}


const ll inv2 = (mod + 1) / 2;
#define dcsl(x, y) (inv2 * (x + y) % mod * (y - x + 1) % mod)
#define sum(x, y) ((psquared[y] - psquared[x - 1] + mod) % mod)

int st[N], len;

ll bruteforce(int bas) {
    len = 0;
    int x = n;
    while (x) {
        st[++len] = x % bas;
        x /= bas;
    }
    ll res = 0, powbas = 1;
    for (int i = len; i >= 1; i--) {
        res = (res + st[i] * powbas) % mod;
        powbas = powbas * bas % mod;
    }
    return res;
}

void solve() {
    cin >> n >> k;
    ans = 0;
    if (k > n) {
        ans += (k - n) % mod * n % mod;
    }
    ll sq = int(sqrt(n));
    int bg = sq + 1, ed = min(ll(n), k);
    // cout<<bg<<" ~ "<<ed<<'\n';
    while (bg <= ed) {
        int l = bg, r = n / (n / bg);
        ll val = n / l;
        // cout<<"VAL = "<<val<<'\n';
        if (r <= ed) {
            ans = (ans + val * (r - l + 1 - sum(l, r) + mod)) % mod;
            ans = (ans + n * dcsl(l, r)) % mod;
        } else {
            ans = (ans + val * (ed - l + 1 - sum(l, ed) + mod)) % mod;
            // cout<<"??? "<<ans<<'\n';
            ans = (ans + n * dcsl(l, ed)) % mod;
            break;
        }
        bg = r + 1;
    }
    sq = min(sq, k);
    // cout<<ans<<'\n';
    for (int p = 2; p <= sq; p++) {
        ans = (ans + bruteforce(p)) % mod;
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    init();
    while (t--) {
        solve();
    }
    return 0;
}
