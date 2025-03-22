#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> deg(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
    int D = 0;
    for (int i = 1; i <= n; i++) {
        D = max(D, deg[i]);
    }
    int cntMax;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == D) cntMax++;
    }
    int candidate = 0;
    int ansK = 0;

    for (int i = 1; i <= n; i++) {
        if (deg[i] < D) {
            candidate = i;
            break;
        }
    }
    if (candidate != 0) {
        ansK = D - 1;
    } else {
        candidate = 1;
        ansK = D;
    }
    cout << ansK << " " << candidate;
    return 0;
}