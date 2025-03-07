#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T> void print(T... a) {
  ((cout << a << ' '), ...);
  cout << "\n";
}
int ti = 1;
int f[57], g[57];
void work() {
  cin >> g[1] >> g[2] >> g[3];
  cin >> f[1] >> f[2] >> f[3];
  sort(g + 1, g + 4);
  sort(f + 1, f + 4);
  if ((g[2] < f[3]) && (g[1] < f[2]))
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  if (ti == 0)
    cin >> ti;
  while (ti--) {
    work();
  }
  return 0;
}