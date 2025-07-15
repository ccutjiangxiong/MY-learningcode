
#include <bits/stdc++.h>
int main() {
    long long seed;
    std::ifstream fin("user_output");
    if (fin >> seed) {
        std::mt19937_64 mt(seed);
        return (mt() % 100000000) != 20250601;
    } else {
        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < 1919810; i++)
            if ((mt() % 100000000) == 20250601) return 0;
        return 1;
    }
}