#include <bits/stdc++.h>
using namespace std;
const int MAXL = 500000 + 5;
const int MOD = 998244353;

struct Node {
    int ch[2], m, dp;
    bool end;
};

static Node trie[MAXL];
static int pw2[MAXL];
static int tot;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // precompute powers of 2 mod
    pw2[0] = 1;
    for (int i = 1; i < MAXL; i++) pw2[i] = int((long long)pw2[i - 1] * 2 % MOD);

    int N;
    cin >> N;

    // init trie root
    tot = 1;
    trie[0].ch[0] = trie[0].ch[1] = -1;
    trie[0].m = trie[0].dp = 0;
    trie[0].end = false;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        int u = 0;
        vector<int> path = {0};

        // insert s
        for (char c : s) {
            int d = (c == 'A' ? 0 : 1);
            if (trie[u].ch[d] == -1) {
                trie[u].ch[d] = tot;
                trie[tot].ch[0] = trie[tot].ch[1] = -1;
                trie[tot].m = trie[tot].dp = 0;
                trie[tot].end = false;
                tot++;
            }
            u = trie[u].ch[d];
            path.push_back(u);
        }
        trie[u].end = true;

        // update dp from leaf up to root
        for (int j = (int)path.size() - 1; j >= 0; j--) {
            int v = path[j];
            trie[v].m++;
            int l = trie[v].ch[0], r = trie[v].ch[1];
            long long prod = 1;
            prod = (l != -1 ? trie[l].dp : 0);
            prod = prod * (r != -1 ? trie[r].dp : 0) % MOD;
            int pick = trie[v].end ? pw2[trie[v].m - 1] : 0;
            trie[v].dp = int((prod + pick) % MOD);
        }

        // answer after inserting i+1-th string
        cout << trie[0].dp << "\n";
    }

    return 0;
}