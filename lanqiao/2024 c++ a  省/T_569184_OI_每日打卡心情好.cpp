#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string date;
    cin >> date;  // 读取今天的日期

    vector<int> punchStatus;
    int status;
    while (cin >> status) {
        punchStatus.push_back(status);
    }

    int consecutiveDays = 0;
    for (int i = punchStatus.size() - 1; i >= 0; --i) {
        if (punchStatus[i] == 1) {
            consecutiveDays++;
        } else {
            break;
        }
    }

    cout << consecutiveDays << endl;
    return 0;
}