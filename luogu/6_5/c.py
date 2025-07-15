def to_base(num, base):
    """Convert non-negative integer num into a base-N string (uppercase for 10–15)."""
    if num == 0:
        return "0"
    digits = []
    while num > 0:
        d = num % base
        if d < 10:
            digits.append(str(d))
        else:
            digits.append(chr(ord('A') + d - 10))
        num //= base
    return "".join(reversed(digits))

def is_pal(s: str) -> bool:
    return s == s[::-1]

def main():
    N = int(input())
    M = input()
    
    
    # simulate up to 30 steps
    for step in range(31):
        if is_pal(M):
            print(f"STEP={step}")
            return
        # do one reverse-and-add
        m_val = int(M, N)
        rev_val = int(M[::-1], N)
        M = to_base(m_val + rev_val, N)
    print("Impossible!")

if __name__ == "__main__":
    main()