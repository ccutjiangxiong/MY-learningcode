import sys
import math
from decimal import Decimal, getcontext

def main():
    n = int(sys.stdin.readline())
    # 提升 Python3.11+ 的“大整数转字符串”限制，否则 Decimal.sqrt 会报错
    sys.set_int_max_str_digits(n*2)

    # 输出整数部分
    sys.stdout.write("3.\n")
    if n <= 0:
        return

    # 为了迭代稳定，设定额外的运算精度
    getcontext().prec = n + 20

    # Gauss–Legendre 初值
    a = Decimal(1)
    b = Decimal(1) / Decimal(2).sqrt()
    t = Decimal(1) / Decimal(4)
    p = Decimal(1)

    # 迭代次数 ≈ log2(n) + 1
    iterations = int(math.log2(n)) + 2
    for _ in range(iterations):
        an = (a + b) / 2
        bn = (a * b).sqrt()
        t -= p * (a - an) ** 2
        a, b = an, bn
        p *= 2

    pi = (a + b) ** 2 / (4 * t)

    # 提取小数部分，补齐到 n 位
    s = str(pi)[2:]
    if len(s) < n:
        s = s + "0" * (n - len(s))
    else:
        s = s[:n]

    # 每 50 位换行，每 10 位空格分隔
    for i in range(0, n, 50):
        chunk = s[i:i+50]
        blocks = [chunk[j:j+10] for j in range(0, len(chunk), 10)]
        sys.stdout.write(" ".join(blocks) + "\n")

if __name__ == "__main__":
    main()