#include <bits/stdc++.h>
using namespace std;
constexpr int Lim = 1e5, MAXN = Lim + 10;
int prime[MAXN], cntprime, fc[MAXN], phi[MAXN], mu[MAXN];
inline void sieve() {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= Lim; ++i) {
        if (!fc[i]) {
            fc[i] = prime[++cntprime] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= cntprime; ++j)
            if (prime[j] * i > Lim)
                break;
            else if (prime[j] == fc[i]) {
                fc[prime[j] * i] = prime[j];
                phi[prime[j] * i] = prime[j] * phi[i];
                mu[prime[j] * i] = 0;
                break;
            } else {
                fc[prime[j] * i] = prime[j];
                phi[prime[j] * i] = phi[prime[j]] * phi[i];
                mu[prime[j] * i] = -mu[i];
            }
    }
}

vector<int> con[MAXN][2], d[MAXN];
inline void init() {
    sieve();
    for (int i = 1; i <= Lim; ++i)
        if (mu[i])
            for (int j = i, k = 1; j <= Lim; j += i, ++k) con[j][mu[i] == 1].push_back(k);
    for (int i = 1; i <= Lim; ++i)
        for (int j = i; j <= Lim; j += i) d[j].push_back(i);
}

static vector<int> cyclo(int n) {
    int deg = phi[n];
    vector<int> a(deg + 1, 0);
    a[0] = 1;
    for (int e : con[n][1])
        for (int i = deg; i >= e; --i) a[i] -= a[i - e];
    for (int e : con[n][0])
        for (int i = e; i <= deg; ++i) a[i] += a[i - e];
    if (a[deg] < 0)
        for (int& v : a) v = -v;
    return a;
}

static string poly2str(const vector<int>& a) {
    string s;
    int D = (int)a.size() - 1;
    for (int i = D; i >= 0; --i) {
        int c = a[i];
        if (c == 0) continue;
        if (!s.empty())
            s += (c > 0 ? '+' : '-');
        else if (c < 0)
            s += '-';
        int v = abs(c);
        if (!(v == 1 && i != 0)) s += to_string(v);
        if (i > 0) {
            s += 'x';
            if (i > 1) {
                s += '^';
                s += to_string(i);
            }
        }
    }
    return s.empty() ? "0" : s;
}

// --- In main(), replace the body with: ---
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();  // builds φ[], μ[], con[][], d[][]

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        // collect divisors
        vector<int>& ds = d[n];
        sort(ds.begin(), ds.end(), [&](int a, int b) {
            auto A = cyclo(a), B = cyclo(b);
            if (A.size() != B.size()) return A.size() < B.size();
            for (int i = (int)A.size() - 1; i >= 0; --i)
                if (A[i] != B[i]) return A[i] < B[i];
            return false;
        });
        // output each factor
        for (int e : ds) {
            auto coef = cyclo(e);
            cout << '(' << poly2str(coef) << ')';
        }
        cout << '\n';
    }
    return 0;
}