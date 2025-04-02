#include <bits/stdc++.h>
using namespace std;

struct te {
    string ch, te;
    int id;
    int type;  
};

bool cmp(const te &a, const te &b) {
    return a.id < b.id;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<te> tes(n);
    unordered_map<string, int> chCount;    
    unordered_set<string> bchs, cchs;  


    for (int i = 0; i < n; i++) {
        cin >> tes[i].ch >> tes[i].te >> tes[i].id;
        tes[i].type = 0;  
    }


    int bs;
    cin >> bs;
    for (int i = 0; i < bs; i++) {
        string ch;
        cin >> ch;
        bchs.insert(ch);
    }

    int cs;
    cin >> cs;
    for (int i = 0; i < cs; i++) {
        string ch;
        cin >> ch;
        cchs.insert(ch);
    }


    sort(tes.begin(), tes.end(), cmp);

    vector<te> al, bList, cList;

    for (auto &te : tes) {
        if (chCount[te.ch] >= 3) continue;  

        if (al.size() < m * 6 / 10) { 
            al.push_back(te);
            chCount[te.ch]++;
        } else if (bchs.count(te.ch) && bList.size() < m * 3 / 10) {  
            bList.push_back(te);
            chCount[te.ch]++;
        } else if (cchs.count(te.ch) && cList.size() < m * 1 / 10) {  
            cList.push_back(te);
            chCount[te.ch]++;
        }
    }

    cout << al.size() << "\n";
    for (auto &te : al) {
        cout << te.ch << " " << te.te << " " << te.id << "\n";
    }


    cout << bList.size() << "\n";
    for (auto &te : bList) {
        cout << te.ch << " " << te.te << " " << te.id << "\n";
    }


    cout << cList.size() << "\n";
    for (auto &te : cList) {
        cout << te.ch << " " << te.te << " " << te.id << "\n";
    }

    return 0;
}