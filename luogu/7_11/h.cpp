#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cerr << #a << " = " << a << endl
#define dd(a) cerr << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define int ll

const int LimBit = 18;
const int M = 1 << LimBit << 1;

int P = 998244353;
inline int kpow(int a, int x, int p = P) {
    int ans = 1;
    for (; x; x >>= 1, a = (ll)a * a % p)
        if (x & 1) ans = (ll)ans * a % p;
    return ans;
}
inline int exgcd(int a, int b, int &x, int &y) {
    static int g;
    return b ? (exgcd(b, a % b, y, x), y -= a / b * x, g) : (x = 1, y = 0, g = a);
}
inline int inv(int a, int p = P) {
    static int x, y;
    return exgcd(a, p, x, y) == 1 ? x + p : -1;
}

namespace Poly {
const db eps = 1e-6, pi = acos(-1);
struct virr {
    db r, i;
    virr(db r_ = 0, db i_ = 0) : r(r_), i(i_) {}
    virr(int x_) : r(x_ >> 15), i(x_ & 32767) {}
    inline virr operator+(const virr &x) const { return virr(r + x.r, i + x.i); }
    inline virr operator-(const virr &x) const { return virr(r - x.r, i - x.i); }
    inline virr operator*(const virr &x) const {
        return virr(r * x.r - i * x.i, r * x.i + i * x.r);
    }

    inline virr operator-() const { return virr(-r, -i); }
    inline virr operator!() const { return virr(r, -i); }
};

struct vir {
    int v;
    vir(int v_ = 0) : v(v_ >= P ? v_ - P : v_) {}
    inline vir operator+(const vir &x) const { return vir(v + x.v); }
    inline vir operator-(const vir &x) const { return vir(v + P - x.v); }
    inline vir operator*(const vir &x) const { return vir((ll)v * x.v % P); }

    inline vir operator-() const { return vir(P - v); }
    inline vir operator!() const { return vir(inv(v)); }
    inline operator int() const { return v; }
};
struct poly : public vector<vir> {
    inline friend ostream &operator<<(ostream &out, const poly &p) {
        if (!p.empty()) out << (int)p[0];
        for (int i = 1; i < sz(p); ++i) out << " " << (int)p[i];
        return out;
    }
};

int N, N_, Stk[M], curStk, rev[M];
vir Inv[M];
virr w[2][M];
inline void init() {
    N_ = -1;
    curStk = 0;
    Inv[1] = 1;
    for (int i = 2; i < P && i < M; ++i) Inv[i] = -vir(P / i) * Inv[P % i];
}

void work() {
    if (N_ == N) return;
    N_ = N;
    int d = __builtin_ctz(N);
    w[0][0] = w[1][0] = virr(1, 0);
    for (int i = 1; i < N; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (d - 1));
        w[0][i] = virr(cos(2 * pi * i / N), sin(2 * pi * i / N));
        w[1][i] = !w[0][i];
    }
}

inline void FFT(virr a[M], int f) {
    static auto make = [=](virr w, virr &a, virr &b) {
        w = w * a;
        a = b - w;
        b = b + w;
    };
    for (int i = 0; i < N; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < N; i <<= 1)
        for (int j = 0, t = N / (i << 1); j < N; j += i << 1)
            for (int k = 0, l = 0; k < i; k++, l += t) make(w[f][l], a[j + k + i], a[j + k]);
    if (f)
        for (int i = 0; i < N; ++i) a[i] = virr(a[i].r / N, a[i].i / N);
}

virr p0[M], p1[M];
inline int mergeNum(ll a1, ll a0, ll b1, ll b0) {
    return ((((a1 << 15) + a0 + b1) % P << 15) + b0) % P;
}
inline void get_mul(poly &a, poly &b, int na, int nb) {  // 4*FFT
    static virr x, y, t0(0, -0.5), t1(0.5, 0);
    for (N = 1; N < na + nb - 1; N <<= 1);
    for (int i = 0; i < na; ++i) p1[i] = (int)a[i];
    for (int i = na; i < N; ++i) p1[i] = virr(0, 0);
    for (int i = 0; i < nb; ++i) p0[i] = (int)b[i];
    for (int i = nb; i < N; ++i) p0[i] = virr(0, 0);
    work();
    FFT(p1, 0);
    FFT(p0, 0);
    for (int i = 0, j; i + i <= N; ++i) {
        j = (N - 1) & (N - i);
        x = p0[i], y = p0[j];
        p0[i] = (x - !y) * p1[i] * t0;
        p1[i] = (x + !y) * p1[i] * t1;
        if (i == j) continue;
        p0[j] = (y - !x) * p1[j] * t0;
        p1[j] = (y + !x) * p1[j] * t1;
    }
    FFT(p1, 1);
    FFT(p0, 1);
    a.resize(na + nb - 1);
    for (int i = 0; i < sz(a); ++i)
        a[i] = mergeNum(p1[i].r + 0.5, p1[i].i + 0.5, p0[i].r + 0.5, p0[i].i + 0.5);
}

poly a, b;
inline void ValueTrans(poly &y, poly &g, int n, int m) {
    // y[i]=f(i),i in [0,n]
    // g[i]=f(m+i),i in [0,n]
    // m>n
    a.resize(2 * n + 1);
    b.resize(2 * n + 1);
    g.resize(n + 1);
    a[0] = m - n;
    for (int i = 1; i <= 2 * n; ++i) a[i] = a[i - 1] * vir(m - n + i);
    b[0] = !a[2 * n];
    for (int i = 2 * n; i; --i) b[i] = b[0] * a[i - 1], b[0] = b[0] * vir(m - n + i);
    g[0] = a[n];
    for (int i = 1; i <= n; ++i) g[i] = g[i - 1] * b[i - 1] * vir(m + i);

    a[0] = 1;
    for (int i = 1; i <= n; ++i) a[i] = a[i - 1] * Inv[i];
    for (int i = 0, j = n; i <= j; ++i, --j) {
        a[i] = a[j] = a[i] * a[j];
        a[i] = a[i] * (j & 1 ? -y[i] : y[i]);
        if (i != j) a[j] = a[j] * (i & 1 ? -y[j] : y[j]);
    }

    get_mul(a, b, n + 1, 2 * n + 1);
    for (int i = 0; i <= n; ++i) g[i] = g[i] * a[i + n];
}

poly c, d;
inline int get_fac(int n) {
    int pos = curStk, s = sqrt(n) + 1e-6;
    vir invs = Inv[s];
    for (int i = s; i > 1; i >>= 1) Stk[++curStk] = i;

    c.resize(2);
    c[0] = 1;
    c[1] = s + 1;
    for (int l = Stk[curStk]; curStk > pos; l = Stk[--curStk]) {
        ValueTrans(c, d, l >> 1, (l >> 1) + 1);
        c.resize(2 * sz(c));
        for (int i = 0; i < sz(d); ++i) c[sz(d) + i] = d[i];
        int x = invs * vir(l >> 1);
        // cout << c.size() << ' ' << x << ' ' << invs << ' ' << s << endl;
        // int u=invs*vir(l>>1);
        ValueTrans(c, d, sz(c) - 1, invs * vir(l >> 1));
        for (int i = 0; i < sz(c); ++i) c[i] = c[i] * d[i];
        if (l & 1) {
            for (int i = 0; i <= l; ++i) c[i] = c[i] * vir(i * s + l);
        } else
            c.resize(l + 1);
        // break;
        cout<<c.size()<<' '<<x<<endl;
    }

    vir res = 1;
    for (int i = s * s + 1; i <= n; ++i) res = res * vir(i);
    for (int i = 0; i < s; ++i) res = res * c[i];
    return res;
}
}  // namespace Poly
using Poly::poly;

int n;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> P;
        Poly::init();
        cout << Poly::get_fac(n) << "\n";
    }
    cout.flush();
    return 0;
}