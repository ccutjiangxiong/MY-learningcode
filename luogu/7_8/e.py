from math import gcd
import sys
sys.set_int_max_str_digits(0)
mod=int(1e9)
phi=4*int(1e8)
while 1:

    n=int(input())
    # print((n+1)*(n+2)*(n)//6%10007);
    if n==0:
        break
    if n<=100:
        ans=12**n-4*(8**n)+6*(4**n)+(-4)**n
        ans=ans//256
    elif n<=phi+5:
        ans=81*pow(12,(n-4),mod)-pow(8,(n-2),mod)+6*pow(4,(n-4),mod)+pow(-4,(n-4),mod)
        ans%=mod
    else:
        ans=81*pow(12,(n-4)%phi+phi,mod)-pow(8,(n-2)%phi+phi,mod)+6*pow(4,(n-4)%phi+phi,mod)+pow(-4,(n-4)%phi+phi,mod)
        ans%=mod
    print((ans+mod)%mod)