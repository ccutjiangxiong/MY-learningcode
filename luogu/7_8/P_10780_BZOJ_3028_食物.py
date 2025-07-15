from math import gcd
import sys
sys.set_int_max_str_digits(0)
n=int(input())
print((n+1)*(n+2)*(n)//6%10007);