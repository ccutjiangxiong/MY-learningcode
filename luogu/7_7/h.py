import sys
sys.set_int_max_str_digits(0)
m = int(input())
n_str = input().strip()
n = int(n_str)

# 根据高精度数的长度确定二分上界
d = len(n_str)
high = 10 ** ((d + m - 1) // m)
low = 0
ans = 0

# 二分查找 x^m <= n < (x+1)^m
while low <= high:
    mid = (low + high) // 2
    if mid**m <= n:
        ans = mid
        low = mid + 1
    else:
        high = mid - 1

print(ans)