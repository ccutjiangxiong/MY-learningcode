#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int  N = 2e6 + 5,mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T> void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti=1;
int n;
int x[N], y[N], c[N];
int bi[N];
int lowbit(int x){
    return x&-x;
}
void update(int x,int v){
    for(;x<=n;x+=lowbit(x))
        bi[x]+=v;
}
void uprange(int l,int r,int v){
    update(l,v);
    update(r+1,-v);
}
int query(int x){
    int ans=0;
    for(;x;x-=lowbit(x))
        ans+=bi[x];
    return ans;
}
map<int,int> mp;
void work() {
    cin >> n;
    rep(i, 1, n) cin >> x[i] >> y[i];
    rep(i, 1, n) c[i] = x[i], c[i + n] = y[i];
    sort(c + 1, c + 1 + n);
    int l = unique(c + 1, c + 1 +2* n)-c-1;
       
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