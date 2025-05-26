t = int(input())
phi      = (1 + 5**0.5) / 2
inv_phi  = phi - 1            
inv_phi2 = inv_phi * inv_phi  
for _ in range(t):
    n = int(input())
    f = [tuple(map(float, input().split())) for _ in range(n)]

    def F(x):
        return max(a*x*x + b*x + c for a, b, c in f)

    l, r = 0.0, 1000.0
    m1 = l + (r - l) * inv_phi2
    m2 = l + (r - l) * inv_phi
    f1 = F(m1)
    f2 = F(m2)
    while abs(f1-f2)>1e-6:
        if f1 < f2:
            r, m2, f2 = m2, m1, f1
            m1 = l + (r - l) * inv_phi2
            f1 = F(m1)
        else:
            l, m1, f1 = m1, m2, f2
            m2 = l + (r - l) * inv_phi
            f2 = F(m2)

    mid = (l + r) / 2
    print(f"{F(mid):.4f}")