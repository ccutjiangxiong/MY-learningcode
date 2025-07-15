#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_cxx;

string a, b, c;
main() {
    ios::sync_with_stdio(0), cin.tie(nullptr);
    cin >> a >> b;
    string c =
        "echo \"import sys;sys.set_int_max_str_digits(100001);exec(\'\'\'a=int(" + a + ");b=int(" +
        b +
        ");l=0;r=1;\nwhile(r**a<=b):\n    l=r;r=r*2\nwhile(l+1<r):\n    mid=(l+r)//2\n    "
        "if(mid**a<=b):\n        l=mid\n    else:\n        r=mid\nif(l**a<=b):\n    "
        "print(l)\nelse:\n    print(r)\'\'\')\" | /nix/var/nix/profiles/judge_python3-c/bin/python";
    system(c.c_str());
}
