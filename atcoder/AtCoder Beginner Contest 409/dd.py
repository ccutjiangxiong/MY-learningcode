def solve():
    import sys
    input = sys.stdin.read().split()
    ptr = 0
    T = int(input[ptr])
    ptr += 1
    for _ in range(T):
        N = int(input[ptr])
        ptr += 1
        S = input[ptr]
        ptr += 1
        if N == 1:
            print(S)
            continue
        l = [S]
        for i in range(N - 1):
            if S[i] > S[i + 1]:
                new_S = S[:i] + S[i+1] + S[i] + S[i+2:]
                l.append(new_S)
                break
        max_char = max(S)
        for i in range(N):
            if S[i] == max_char:
                new_S = S[:i] + S[i+1:] + S[i]
                l.append(new_S)
                break
        res = min(l)
        print(res)

solve()