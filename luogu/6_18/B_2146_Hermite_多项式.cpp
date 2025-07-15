#include <cmath>
#include <cstdio>

int n, x;
int main() {
    scanf("%d%d", &n, &x);
    printf("%.0f\n", std::hermite(n, x));
    return 0;
}
