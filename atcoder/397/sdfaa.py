import math

def find_xy(N):
    max_d = int(round(N ** (1/3))) + 1
    for d in range(1, max_d + 1):
        if N % d != 0:
            continue
        target = N // d
        discriminant = 12 * target - 3 * d**2
        if discriminant < 0:
            continue
        sqrt_discriminant = math.isqrt(discriminant)
        if sqrt_discriminant * sqrt_discriminant != discriminant:
            continue
        numerator = -3 * d + sqrt_discriminant
        if numerator % 6 != 0:
            continue
        y = numerator // 6
        if y <= 0:
            continue
        x = y + d
        return x, y
    return -1

# Example usage:
N = int(input())
result = find_xy(N)
if result == -1:
    print(-1)
else:
    print(result[0], result[1])