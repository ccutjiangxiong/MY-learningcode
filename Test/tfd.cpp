#include <iostream>
using namespace std;

int main() {
    int n1, n2;

    cout << "输入两个整数: ";
    cin >> n1 >> n2;

    while(n1) 
    {
        if (n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
 
    cout << "HCF = " << n1;
    return 0;
}
