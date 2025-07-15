import sys
import decimal

def main():
    n = int(sys.stdin.readline())
    # 为了保证累加足够精度，多开几个 guard 位
    decimal.getcontext().prec = 3300
    one = decimal.Decimal(1)
    e = decimal.Decimal(0)
    fact = decimal.Decimal(1)
    i = 0
    # 用泰勒级数累加 1/k!，直到下一项小于 10^{-(n+5)} 时停止
    while True:
        if i > 0:
            fact *= i
        term = one / fact
        if term < decimal.Decimal(10) ** (-(n + 5)):
            break
        e += term
        i += 1

    # 转成字符串，截取或补齐小数部分
    s = format(e, 'f')
    if '.' in s:
        intpart, frac = s.split('.')
    else:
        intpart, frac = s, ''
    frac = (frac + '0' * n)[:n]

    # 输出
    # 第一行 "2."
    print(f"{intpart}.")
    # 小数部分每 50 位一行，每行内部每 10 位加一个空格
    for pos in range(0, n, 50):
        line = frac[pos:pos+50]
        groups = [line[k:k+10] for k in range(0, len(line), 10)]
        print(' '.join(groups))

if __name__ == "__main__":
    main()