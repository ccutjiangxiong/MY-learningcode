import sys
from decimal import Decimal, getcontext

getcontext().prec = 100000 

for line in sys.stdin:
    n, m = map(Decimal, line.split())
    s = '{0:f}'.format(n**m)
    if '.' in s:
        s = s.rstrip('0').rstrip('.')
        
    if s.startswith('0.'):
        s = s[1:]  
    
    print(s)