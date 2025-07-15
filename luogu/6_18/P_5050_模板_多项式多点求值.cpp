#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int MOD = 998244353;
const int g = 3, gi = 332748118;

template <const int mod>
class modInt {
   public:
    int num;
    modInt(int x = 0) : num(x % mod) {
        if (num < 0) num += mod;
    }
    static modInt fastPow(modInt a, long long b) {
        modInt res(1);
        if (b < 0) return fastPow(inv(a), -b);
        while (b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }
    static modInt inv(const modInt& a) { return fastPow(a, mod - 2); }
    modInt operator+(const modInt& o) const { return modInt(num + o.num); }
    modInt operator-(const modInt& o) const { return modInt(num - o.num); }
    modInt operator*(const modInt& o) const { return modInt((long long)num * o.num % mod); }
    modInt operator/(const modInt& o) const { return *this * inv(o); }
    modInt& operator+=(const modInt& o) {
        num = (num + o.num) % mod;
        return *this;
    }
    modInt& operator-=(const modInt& o) {
        num = (num - o.num + mod) % mod;
        return *this;
    }
    modInt& operator*=(const modInt& o) {
        num = (long long)num * o.num % mod;
        return *this;
    }
    modInt& operator/=(const modInt& o) { return *this *= inv(o); }
    friend ostream& operator<<(ostream& os, const modInt& x) { return os << x.num; }
    friend istream& operator>>(istream& is, modInt& x) { return is >> x.num; }
};

using mint = modInt<MOD>;

void NTT(vector<mint>& A, int op) {
    int n = A.size();
    vector<int> R(n);
    rep(i, 0, n - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    rep(i, 0, n - 1) if (i < R[i]) swap(A[i], A[R[i]]);
    for (int len = 2; len <= n; len <<= 1) {
        mint wn = mint(op == 1 ? g : gi);
        wn = mint::fastPow(wn, (MOD - 1) / len);
        for (int i = 0; i < n; i += len) {
            mint w(1);
            for (int j = 0; j < len / 2; j++) {
                mint u = A[i + j], v = A[i + j + len / 2] * w;
                A[i + j] = u + v;
                A[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }
    if (op == -1) {
        mint inv_n = mint::fastPow(mint(n), MOD - 2);
        rep(i, 0, n - 1) A[i] *= inv_n;
    }
}

class Poly {
    vector<mint> a;

   public:
    Poly() {}
    Poly(const vector<mint>& v) : a(v) { normalize(); }
    void normalize() {
        while (!a.empty() && a.back().num == 0) a.pop_back();
    }
    int deg() const { return (int)a.size() - 1; }
    mint operator[](int i) const { return i < (int)a.size() ? a[i] : mint(0); }
    vector<mint> data() const { return a; }

    Poly operator+(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vector<mint> c(n);
        rep(i, 0, n - 1) c[i] = (*this)[i] + b[i];
        return Poly(c);
    }
    Poly operator-(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vector<mint> c(n);
        rep(i, 0, n - 1) c[i] = (*this)[i] - b[i];
        return Poly(c);
    }
    Poly operator*(const Poly& b) const {
        auto A = a, B = b.a;
        if (A.empty() || B.empty()) return Poly();
        int sz = 1, n = A.size(), m = B.size();
        while (sz < n + m - 1) sz <<= 1;
        A.resize(sz);
        B.resize(sz);
        NTT(A, 1);
        NTT(B, 1);
        rep(i, 0, sz - 1) A[i] *= B[i];
        NTT(A, -1);
        A.resize(n + m - 1);
        return Poly(A);
    }
    mint eval(mint x) const {
        mint res = 0;
        for (int i = deg(); i >= 0; i--) res = res * x + a[i];
        return res;
    }
    Poly operator%(const Poly& b) const { return Poly(poly_mod(a, b.a)); }
    static vector<mint> poly_inv(vector<mint> A, int n) {
        if (n == 1) return {mint::fastPow(A[0], MOD - 2)};
        int m = (n + 1) >> 1;
        A.resize(n);
        auto B = poly_inv(A, m);
        int sz = 1;
        while (sz < 2 * n) sz <<= 1;
        A.resize(sz);
        B.resize(sz);
        NTT(A, 1);
        NTT(B, 1);
        rep(i, 0, sz - 1) B[i] = (mint(2) - A[i] * B[i]) * B[i];
        NTT(B, -1);
        B.resize(n);
        return B;
    }
    static vector<mint> multiply_ntt(vector<mint> A, vector<mint> B) {
        if (A.empty() || B.empty()) return {};
        int n = A.size(), m = B.size(), sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        A.resize(sz);
        B.resize(sz);
        NTT(A, 1);
        NTT(B, 1);
        rep(i, 0, sz - 1) A[i] *= B[i];
        NTT(A, -1);
        A.resize(n + m - 1);
        return A;
    }
    static vector<mint> poly_div(vector<mint> A, vector<mint> B) {
        int n = A.size(), m = B.size();
        if (n < m) return {};
        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());
        auto Q = multiply_ntt(A, poly_inv(B, n - m + 1));
        Q.resize(n - m + 1);
        reverse(Q.begin(), Q.end());
        return Q;
    }
    static vector<mint> poly_mod(vector<mint> A, vector<mint> B) {
        int n = A.size(), m = B.size();
        if (n < m) {
            A.resize(max(0LL, m - 1));
            return A;
        }
        auto Q = poly_div(A, B);
        auto C = multiply_ntt(Q, B);
        C.resize(n);
        vector<mint> R(n);
        rep(i, 0, n - 1) R[i] = A[i] - C[i];
        R.resize(m - 1);
        return R;
    }
    vector<mint> eval(const vector<mint>& xs) const {
        int m = xs.size();
        if (m == 0) return {};
        vector<Poly> seg(4 * m);
        vector<mint> res(m);
        auto build = [&](auto&& self, int o, int l, int r) -> void {
            if (l == r) {
                seg[o] = Poly(vector<mint>{mint(0) - xs[l], mint(1)});
            } else {
                int mid = (l + r) >> 1;
                self(self, o << 1, l, mid);
                self(self, o << 1 | 1, mid + 1, r);
                seg[o] = seg[o << 1] * seg[o << 1 | 1];
            }
        };
        auto dfs = [&](auto&& self, int o, int l, int r, const Poly& f) -> void {
            Poly rmd = f % seg[o];
            if (l == r)
                res[l] = rmd.eval(xs[l]);
            else {
                int mid = (l + r) >> 1;
                self(self, o << 1, l, mid, rmd);
                self(self, o << 1 | 1, mid + 1, r, rmd);
            }
        };
        build(build, 1, 0, m - 1);
        dfs(dfs, 1, 0, m - 1, *this);
        return res;
    }
};

void work() {
    int n, m;
    cin >> n >> m;
    vector<mint> A(n + 1);
    rep(i, 0, n) cin >> A[i];
    vector<mint> xs(m);
    rep(i, 0, m - 1) cin >> xs[i];
    Poly F(A);
    auto ys = F.eval(xs);
    rep(i, 0, m - 1) cout << ys[i] << "\n";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    if (T == 0) cin >> T;
    while (T--) work();
    return 0;
}