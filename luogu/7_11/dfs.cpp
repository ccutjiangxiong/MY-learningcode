template <const int mod>
struct modInt {
    modInt(const int x = 0) : num((x % mod + mod) % mod) {}
    explicit operator int() { return num; }
    static constexpr int phi_v = mod - 1;
    static modInt fastPow(modInt a, int b) {
        if (b < 0) return fastPow(inv(a), -b);
        b = b % (phi_v)
        modInt res(1);
        for (; b; a = a * a, b >>= 1)
            if (b & 1) res = res * a;
        return res;
    }
    template <typename... Ts>
    modInt pow(Ts... exps) const {
        int e = 1;
        ((e = ((__int128)e * ((exps % phi_v + phi_v) % phi_v)) % phi_v), ...);
        return fastPow(*this, e);
    }
    static modInt sqrt(const modInt& n) {
        if (n.num == 0) return 0;
        if (n.pow((mod - 1) / 2) != 1) return -1;
        int S = 0, q = mod - 1;
        while (!(q & 1)) q >>= 1, ++S;
        modInt z = 2;
        while (z.pow((mod - 1) / 2) != modInt(mod - 1)) ++z;
        modInt c = z.pow(q);
        modInt x = n.pow((q + 1) / 2);
        modInt t = n.pow(q);
        int M = S;
        while (t != 1) {
            int i = 1;
            modInt tt = t * t;
            while (tt != 1) tt = tt * tt, ++i;
            modInt b = c.pow(1LL << (M - i - 1));
            x *= b, c = b * b;
            t *= c, M = i;
        }
        modInt r1 = x, r2 = -x;
        return r1 < r2 ? r1 : r2;
    }
    static modInt inv(const modInt x) { return fastPow(x, mod - 2); }
    friend std::ostream& operator<<(std::ostream& ou, const modInt& x) { return ou << x.num, ou; }
    friend std::istream& operator>>(std::istream& in, modInt& x) { return in >> x.num, in; }
    constexpr modInt& operator+=(const modInt& o) noexcept { return (num += o.num) %= mod, *this; }
    constexpr modInt& operator-=(const modInt& o) noexcept {return  *this+=-o;}
    constexpr modInt& operator*=(const modInt& o) noexcept { return (num *= o.num) %= mod, *this; }
    constexpr modInt& operator/=(const modInt& o) noexcept { return *this *= inv(o); }
    friend constexpr modInt operator^(modInt a, int e) noexcept { return fastPow(a, e); }
    constexpr modInt operator-() const noexcept { return (mod-num)%mod; }
    friend constexpr auto operator<=>(const modInt& a, const modInt& b) noexcept = default;
    constexpr modInt& operator++() noexcept { return *this += 1; }
    constexpr modInt& operator--() noexcept { return *this -= 1; }
    friend constexpr auto operator+(modInt a, const auto& b) noexcept { return a += b; }
    friend constexpr auto operator-(modInt a, const auto& b) noexcept { return a -= b; }
    friend constexpr auto operator*(modInt a, const auto& b) noexcept { return a *= b; }
    friend constexpr auto operator/(modInt a, const auto& b) noexcept { return a /= b; }
    int num;
};
const int MOD = 998244353;
using mint = modInt<MOD>;
using vmi = vector<mint>;
const int p = 998244353, g = 3, gi = 332748118;
static int NTT_n = 0, NTT_logn = 0;
static vi R;
static vector<vmi> wn[2];
void NTT(vmi& a, int op) {
    int n = a.size();
    if (n != NTT_n) {
        NTT_n = n, NTT_logn = lbt(n), R.assign(n, 0);
        rep(i, 0, n - 1) R[i] = R[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
        for (int t = 0; t < 2; t++) {
            wn[t].assign(NTT_logn + 1, {});
            for (int k = 1; k <= NTT_logn; k++) {
                int len = 1 << k, half = len >> 1;
                mint b = mint(t == 0 ? g : gi).pow((p - 1) / len);
                auto& w = wn[t][k];
                w.resize(half), w[0] = 1;
                rep(i, 1, half - 1) w[i] = w[i - 1] * b;
            }
        }
    }
    rep(i, 0, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
    for (int k = 1, len = 2; k <= NTT_logn; k++, len <<= 1) {
        int half = len >> 1;
        auto& w = wn[op == 1 ? 0 : 1][k];
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < half; j++) {
                mint u = a[i + j];
                mint v = a[i + j + half] * w[j];
                a[i + j] = u + v;
                a[i + j + half] = u - v;
            }
    }
    if (op == -1) {
        mint inv_n = mint::inv(n);
        for (auto& x : a) x *= inv_n;
    }
}

class Poly {
   public:
    vmi a;
    Poly() = default;
    Poly(vmi  v) : a(std::move(v)) { normalize(); }
    void normalize() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }
    int deg() const { return (int)a.size() - 1; }

   private:
    static vmi multiply_ntt(vmi A, vmi B) {
        int n = A.size(), m = B.size();
        if (n == 0 || m == 0) return {};
        int sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        A.resize(sz), B.resize(sz);
        NTT(A, 1), NTT(B, 1);
        rep(i, 0, sz - 1) A[i] *= B[i];
        NTT(A, -1), A.resize(n + m - 1);
        return A;
    }
    static vmi poly_inv(vmi A, int n) {
        if (n == 1) return {mint::inv(A[0])};
        int m = (n + 1) >> 1, len = 1;
        A.resize(n);
        auto B = poly_inv(A, m);
        while (len < 2 * n) len <<= 1;
        A.resize(len), B.resize(len);
        NTT(A, 1), NTT(B, 1);
        for (int i = 0; i < len; ++i) B[i] = (mint(2) - A[i] * B[i]) * B[i];
        NTT(B, -1), B.resize(n);
        return B;
    }
    static vmi poly_div(vmi A, vmi B) {
        int n = A.size(), m = B.size();
        if (n < m) return {};
        rg::reverse(A), rg::reverse(B);
        B = poly_inv(B, n - m + 1);
        auto Qr = multiply_ntt(A, B);
        Qr.resize(n - m + 1);
        rg::reverse(Qr);
        return Qr;
    }
    static vmi poly_mod(vmi A, vmi B) {
        int n = A.size(), m = B.size();
        if (n < m) return (A.resize(m - 1), A);
        auto Q = poly_div(A, B);
        auto C = multiply_ntt(Q, B);
        auto R = (Poly(A) - Poly(C)).a;
        R.resize(m - 1);
        return R;
    }

    static vmi poly_derivative(const vmi& A) {
        int n = A.size();
        if (n <= 1) return {mint(0)};
        vmi D(n - 1);
        for (int i = 1; i < n; i++) D[i - 1] = A[i] * i;
        return D;
    }
    static vmi poly_integral(const vmi& A) {
        int n = A.size();
        vmi I(n + 1);
        I[0] = 0;
        for (int i = 0; i < n; i++) I[i + 1] = A[i] / (i + 1);
        return I;
    }
    // 多项式 ln(A) mod x^n，要求 A[0]=1
    static vmi poly_ln(vmi A, int n) {
        A.resize(n);
        auto D = poly_derivative(A);
        auto Inv = poly_inv(A, n);
        auto tmp = multiply_ntt(D, Inv);
        tmp.resize(n - 1);
        auto L = poly_integral(tmp);
        L.resize(n);
        return L;
    }
    // 多项式 exp(A) mod x^n，要求 A[0]=0
    static vmi poly_exp(vmi A, int n) {
        if (n == 1) return {mint(1)};
        int m = (n + 1) >> 1;
        auto B = poly_exp(A, m);
        auto lnB = poly_ln(B, n);
        vmi diff(n);
        for (int i = 0; i < n; i++) diff[i] = (i < (int)A.size() ? A[i] : mint(0)) - lnB[i];
        diff[0] += 1;
        auto C = multiply_ntt(B, diff);
        C.resize(n);
        return C;
    }
    static vector<mint> poly_sqrt(vector<mint> A, int n) {
        if (n == 1) {
            mint r = mint::sqrt(A[0]);
            return {r};
        }
        int m = (n + 1) >> 1;
        auto B = poly_sqrt(A, m);
        auto InvB = poly_inv(B, n);
        auto C = multiply_ntt(A, InvB);
        C.resize(n);
        B.resize(n);
        mint inv2 = mint::inv(mint(2));
        vector<mint> S(n);
        rep(i, 0, n - 1) S[i] = (B[i] + C[i]) * inv2;

        return S;
    }
    static void build_seg(const vmi& xs, vector<Poly>& seg, int o, int l, int r) {
        if (l == r)
            seg[o] = Poly({-xs[l], mint(1)});
        else {
            int m = (l + r) >> 1;
            build_seg(xs, seg, o << 1, l, m);
            build_seg(xs, seg, o << 1 | 1, m + 1, r);
            seg[o] = seg[o << 1] * seg[o << 1 | 1];
        }
    }
   public:
    vmi eval(const vmi& xs) const {
        int m = xs.size();
        if (!m) return {};
        vector<Poly> seg(4 * m);
        vmi res(m);
        build_seg(xs, seg, 1, 0, m - 1);
        auto dfs = [&](auto&& self, int o, int l, int r, const Poly& f) -> void {
            Poly rmd = f % seg[o];
            if (l == r)
                res[l] = rmd.eval(xs[l]);
            else {
                int mid = (l + r) >> 1;
                self(self, o << 1, l, mid, rmd), self(self, o << 1 | 1, mid + 1, r, rmd);
            }
        };
        dfs(dfs, 1, 0, m - 1, *this);
        return res;
    }
    static Poly interpolate(const vmi& xs, const vmi& ys) {
        int n = xs.size();
        vector<Poly> seg(4 * n), gt(4 * n);
        build_seg(xs, seg, 1, 0, n - 1);
        vmi dcoef = poly_derivative(seg[1].a);
        Poly Tp(dcoef);
        vmi dval = Tp.eval(xs);
        vmi w(n);
        rep(i, 0, n - 1) w[i] = ys[i] / dval[i];
        function<void(int, int, int)> dfs = [&](int o, int l, int r) {
            if (l == r)
                gt[o] = Poly({w[l]});
            else {
                int m = (l + r) >> 1;
                dfs(o << 1, l, m), dfs(o << 1 | 1, m + 1, r);
                gt[o] = gt[o << 1] * seg[o << 1 | 1] + gt[o << 1 | 1] * seg[o << 1];
            }
        };
        dfs(1, 0, n - 1);
        return gt[1];
    }
    static vmi shifted_eval(int m, const vmi& y) {
        int n = sz(y) - 1;
        vmi f(n + 1), invf(n + 1);
        f[0] = 1;
        rep(i, 1, n) f[i] = f[i - 1] * i;
        invf[n] = mint::inv(f[n]);
        rem(i, n, 1) invf[i - 1] = invf[i] * i;
        vmi u(n + 1);
        rep(i, 0, n) {
            mint a = ((n - i) & 1) ? mint(-1) : mint(1);
            u[i] = y[i] * a * invf[i] * invf[n - i];
        }
        vmi v(2 * n + 1);
        rep(k, 0, 2 * n) v[k] = mint::inv(mint(m - n + k));
        auto conv = (Poly(u) * Poly(v)).a;
        mint P = 1;
        rep(k, m - n, m) P *= k;
        vmi res(n + 1);
        for (int x = 0; x <= n; x++) {
            res[x] = conv[n + x] * P;
            if (x < n) P = P * mint(m + x + 1) * v[x];
        }
        return res;
    }
    Poly pow(const string& K, int n) const {
        vmi R(n), Bv = a, C;
        if (K == "0") return R[0] = 1, R;
        int m = a.size(), l = 0;
        while (l < m && a[l] == 0) ++l;
        if (l >= m) return vmi(n, 0);
        if (l > 0) {
            int ne = (n + l - 1) / l;
            string s = std::to_string(ne);
            bool ge = (sz(K) > sz(s) || (sz(K) == sz(s)) && K >= s);
            if (ge) return vmi(n, 0);
            int kll = 0;
            for (char c : K) kll = kll * 10 + (c - '0');
            int sh = l * kll;
            for (int i = l; i < m && sz(C) < n - sh; i++) C.push_back(a[i]);
            Poly PC(C), PD = PC.pow(K, n - sh);
            vmi R(n, 0), vD = PD.a;
            for (int i = 0; i < sz(vD); i++) R[i + sh] = vD[i];
            return Poly(R);
        }
        int km = 0, kph = 0, phi = MOD - 1;
        for (char c : K) km = (km * 10 + (c - '0')) % MOD, kph = (kph * 10 + (c - '0')) % phi;
        Bv.resize(n);
        mint a0 = Bv[0], inv_a0 = mint::inv(a0);
        for (auto& x : Bv) x *= inv_a0;
        auto L = poly_ln(Bv, n);
        for (auto& x : L) x *= km;
        auto S = poly_exp(L, n);
        mint a0k = a0.pow(kph);
        for (auto& x : S) x *= a0k;
        return S;
    }
    mint& operator[](int i) {
        if (i >= (int)a.size()) a.resize(i + 1);
        return a[i];
    }
    mint operator[](int i) const { return (i < (int)a.size() ? a[i] : mint(0)); }
    Poly operator+(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vmi c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] + b[i];
        return Poly(c);
    }
    Poly operator-(const Poly& b) const {
        int n = max(a.size(), b.a.size());
        vmi c(n);
        for (int i = 0; i < n; ++i) c[i] = (*this)[i] - b[i];
        return Poly(c);
    }
    Poly operator*(const Poly& b) const { return Poly(multiply_ntt(a, b.a)); }
    Poly operator/(const Poly& b) const { return Poly(poly_div(a, b.a)); }
    Poly operator%(const Poly& b) const { return Poly(poly_mod(a, b.a)); }
    Poly sqrt(int n) const { return Poly(poly_sqrt(a, n)); }
    Poly inv(int n) const { return Poly(Poly::poly_inv(a, n)); }
    Poly exp(int n) const { return Poly(poly_exp(a, n)); }
    Poly ln(int n) const { return Poly(poly_ln(a, n)); }
    Poly de() const { return poly_derivative(a); }
    Poly inte() const { return poly_integral(a); }
    mint eval(mint x) const {
        mint res = 0;
        for (int i = deg(); i >= 0; --i) res = res * x + a[i];
        return res;
    }
};