#include <bits/extc++.h>
using namespace std;

struct Node {
    int l, r, v;
    Node(int _l, int _r, int _v) : l(_l), r(_r), v(_v) {}
    bool operator<(const Node &u) const { return l < u.l; }
};

set<Node> s;
multiset<int> lens;
long long sum;

auto split(int p) {
    auto it = s.lower_bound(Node(p, 0, 0));
    if (it != s.end() && it->l == p) return it;
    --it;
    int L = it->l, R = it->r, V = it->v;
    s.erase(it);
    s.insert(Node(L, p - 1, V));
    return s.emplace(Node(p, R, V)).first;
}

void merge_adjacent(set<Node>::iterator it) {
    if (it == s.end()) return;
    if (it != s.begin()) {
        auto pit = prev(it);
        if (pit->v == it->v && pit->r + 1 == it->l) {
            int L = pit->l, R = it->r, V = it->v;
            if (V == 1) {
                int l1 = pit->r - pit->l + 1, l2 = it->r - it->l + 1;
                lens.erase(lens.find(l1));
                lens.erase(lens.find(l2));
                lens.insert(R - L + 1);
            }
            s.erase(pit);
            it = s.erase(it);
            it = s.emplace(L, R, V).first;
        }
    }
    auto nit = next(it);
    if (nit != s.end() && nit->v == it->v && it->r + 1 == nit->l) {
        int L = it->l, R = nit->r, V = it->v;
        if (V == 1) {
            int l1 = it->r - it->l + 1, l2 = nit->r - nit->l + 1;
            lens.erase(lens.find(l1));
            lens.erase(lens.find(l2));
            lens.insert(R - L + 1);
        }
        s.erase(it);
        s.erase(nit);
        auto jt = s.emplace(L, R, V).first;
        if (jt != s.begin()) merge_adjacent(jt);
    }
}

void assign(int l, int r, int V) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) {
        if (it->v == 1) {
            int len = it->r - it->l + 1;
            sum -= len;
            lens.erase(lens.find(len));
        }
    }
    s.erase(itl, itr);
    auto itn = s.emplace(Node(l, r, V)).first;
    if (V == 1) {
        sum += (r - l + 1);
        lens.insert(r - l + 1);
    }
    merge_adjacent(itn);
}

void invert(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    vector<Node> tmp(itl, itr);
    s.erase(itl, itr);
    for (auto &nd : tmp) {
        int L = nd.l, R = nd.r, V = nd.v, len = R - L + 1;
        if (V == 1) {
            sum -= len;
            lens.erase(lens.find(len));
        } else {
            sum += len;
            lens.insert(len);
        }
        auto itn = s.emplace(Node(L, R, V ^ 1)).first;
        merge_adjacent(itn);
    }
}

void work() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    s.clear();
    lens.clear();
    sum = 0;
    for (int i = 0; i < n;) {
        int j = i + 1;
        while (j < n && a[j] == a[i]) ++j;
        s.emplace(Node(i, j - 1, a[i]));
        if (a[i] == 1) {
            int len = j - i;
            sum += len;
            lens.insert(len);
        }
        i = j;
    }
    while (m--) {
        int op, L, R;
        cin >> op >> L >> R;
        if (op == 0 || op == 1)
            assign(L, R, op);
        else if (op == 2)
            invert(L, R);
        else if (op == 3) {
            auto itr = split(R + 1), itl = split(L);
            long long cnt = 0;
            for (auto it = itl; it != itr; ++it)
                if (it->v == 1) cnt += it->r - it->l + 1;
            cout << cnt << "\n";
        } else {
            auto itr = split(R + 1), itl = split(L);
            long long best = 0;
            for (auto it = itl; it != itr; ++it)
                if (it->v == 1) best = max(best, (long long)(it->r - it->l + 1));
            cout << best << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    work();
    return 0;
}