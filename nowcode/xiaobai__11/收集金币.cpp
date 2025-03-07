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
int n, m, t;
int mat[1010][1010];
int f[1111][1111];


int dp[1111][1111];

void work() {
  cin >> n >> m;
  rep(i, 1, n) rep(j, 1, m) cin >> mat[i][j];
  cin >> t;
  rep(i, 1, t) {
    int x, y, v;
    cin >> x >> y >> v;
    f[x][y] = v;
  }
  int ans=dp[1][1] = mat[1][1];
  rep(i, 1, n) rep(j, 1, m) if ((i + j - 2 < f[i][j]) || f[i][j] == 0) {
    if (dp[i - 1][j])
      dp[i][j] = dp[i - 1][j] + mat[i][j];
    if (dp[i][j - 1])
      dp[i][j] = max(dp[i][j], dp[i][j - 1] + mat[i][j]);
    ans=max(ans,dp[i][j]);
  }
  //   rep(i, 1, n) {
  //     rep(j, 1, m) cout << dp[i][j] << ' ';
  //     cout << endl;
  //   }
  cout << ans << endl;
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