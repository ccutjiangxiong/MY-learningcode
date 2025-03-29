#include <bits/stdc++.h>

#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
const double PI = numbers::pi;
struct Point {
    double x, y;
    // 构造函数
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    // 运算符重载
    Point operator-(const Point &b) const { return {x - b.x, y - b.y}; }
    Point operator*(double t) const { return {x * t, y * t}; }
    // 叉积
    double operator*(const Point &b) const { return x * b.y - y * b.x; }
    Point operator+(const Point &b) const { return {x + b.x, y + b.y}; }
    // 点积
    double operator&(const Point &b) const { return x * b.x + y * b.y; }
    Point operator/(double t) const { return {x / t, y / t}; }
    // 向量长度
    double len() const { return sqrt(x * x + y * y); }
    // 夹角
    double angle(const Point &b) const { return acos((*this) & b / len() / b.len()); }
    double dis(const Point &b) const { return sqrt((b.x - x) * (b.x - x) + (b.y - y) * (b.y - y)); }
} p[N];
struct Line {
    Point s, e;
} a[N], q[N];
double dot(Point a, Point b, Point c) { return (b - a) & (c - a); }
double cross(Point a, Point b, Point c) { return (b - a) * (c - a); }
// 直线ab余线段cd无交点
double inte_p(Point a, Point b, Point c, Point d) { return cross(a, b, c) * cross(a, b, d); }
// 线段ab与线段cd无交点
double inte_p2(Point a, Point b, Point c, Point d) {
    return inte_p(a, b, c, d) > 0 || inte_p(c, d, a, b);
}
// 求直线交点
Point getNode(Point a, Point u, Point b, Point v) {
    double t = (a - b) * v / (v * u);
    return a + u * t;
}
// 扇形面积
double sector(Point a, Point b, double r) {
    double angle = a.angle(b);
    if (a * b < 0) angle *= -1;
    return r * r * angle / 2;
}
Point rotate(Point a, double b) {
    return {a.x * cos(b) - a.y * sin(b), a.x * sin(b) + a.y * cos(b)};
}
Point norm(Point a) { return a / a.len(); }
bool onSegment(Point p, Point a, Point b) {
    return fabs((a - p) * (b - p)) < eps && ((a - p) & (b - p)) <= 0;
}
// 获得直线与圆的两个交点
double getDP2(Point a, Point b, Point &pa, Point &pb, Point o, double r) {
    Point e = getNode(a, b - a, o, rotate(b - a, PI / 2));
    double d = o.dis(e);
    if (!onSegment(e, a, b)) d = min(o.dis(a), o.dis(b));
    if (r <= d) return d;
    double len = sqrt(r * r - o.dis(e) * o.dis(e));
    pa = e + norm(a - b) * len;
    pb = e + norm(b - a) * len;
    return d;
}
// 三角剖分
double getArea(Point a, Point b, Point o, double r) {
    if (fabs(a * b) < eps) return 0;
    double da = o.dis(a), db = o.dis(b);
    if (r >= max(da, db)) return a * b / 2;
    Point pa, pb;
    double d = getDP2(a, b, pa, pb, o, r);
    if (r <= d) return sector(a, b, r);
    if (r >= da) return a * pb / 2 + sector(a, b, r);
    if (r >= da) return sector(a, pa, r) + pa * b / 2;
    return sector(a, pa, r) + pa * pb / 2 + sector(pb, b, r);
}

double angle(Line a) { return atan2(a.e.y - a.s.y, a.e.x - a.s.x); }
bool cmp(Line a, Line b) {
    double A = angle(a), B = angle(b);
    return fabs(A - B) > eps ? A < B : (a.e - a.s) * (b.e - a.s) < 0;
}
Point cross(Line a, Line b) {
    Point u = a.s - b.s, v = a.e - a.s, w = b.e - b.s;
    double t = u * w / (w * v);
    return a.s + v * t;
}
bool right(Line a, Line b, Line c) {
    Point p = cross(b, c);
    return (a.e - a.s) * (p - a.s) < 0;
}
int n;
void half_plane() {
    sort(a + 1, a + 1 + n, cmp);
    int h = 1, t = 1;
    q[1] = a[1];
    rep(i, 2, n) {
        if (angle(a[i]) - angle(a[i - 1]) < eps) continue;
        while (h < t && right(a[i], q[t], q[t - 1])) t--;
        while (h < t && right(a[i], q[h], q[h + 1])) h++;
        q[++t] = a[i];
    }
    while (h < t && right(q[h], q[t], q[t - 1])) t--;
}
void work() {}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}