mod = 998244353
max_exp = 500000
pow2 = [1] * (max_exp + 1)
for i in range(1, max_exp + 1):
    pow2[i] = (pow2[i - 1] * 2) % mod

import sys

def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index:index + n]))
        index += n
        k = a.count(-1)
        total = 0
        if a[0] == 0:
            pass
        elif a[0] == 1:
            total = (total + pow2[k]) % mod
        else:
            if k >= 1:
                total = (total + pow2[k - 1]) % mod
        for i in range(1, n):
            if a[i] == 0:
                continue
            if a[i - 1] == 1:
                continue
            c = 0
            if a[i] == -1:
                c += 1
            if a[i - 1] == -1:
                c += 1
            if k - c >= 0:
                total = (total + pow2[k - c]) % mod
        results.append(str(total))
    print("\n".join(results))

if __name__ == "__main__":
    main()