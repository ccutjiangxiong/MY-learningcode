import sys, math

def main():
    data = sys.stdin.read().strip()
    if not data:
        return
    P = int(data)
    # 1) 位数 = floor(P * log10(2)) + 1
    digit_count = int(math.floor(P * math.log10(2))) + 1
    print(digit_count)

    # 2) 后500位: compute (2^P mod 10^500) - 1 mod 10^500
    MOD = 10**500
    last = pow(2, P, MOD)
    last = (last - 1) % MOD

    s = str(last).zfill(500)
    for i in range(0, 500, 50):
        print(s[i:i+50])

if __name__ == "__main__":
    main()