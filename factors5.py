#!/usr/bin/python3
import sys
import subprocess

def install(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

# install("gmpy2")
import gmpy
from gmpy import mpz, gcd


def pollard_rho(n):
    if n % 2 == 0:
        return 2

    x = gmpy2.mpz_random(gmpy2.random_state(), n)
    y = x
    c = gmpy2.mpz_random(gmpy2.random_state(), n)
    d = 1

    while d == 1:
        x = (x * x + c) % n
        y = (y * y + c) % n
        y = (y * y + c) % n
        d = gcd(abs(x - y), n)

    return d

def factors(filename):
    with open(filename, 'r') as f:
        for line in f:
            n = mpz(line.strip())
            p = pollard_rho(n)
            q = n // p
            print(f"{n}={p}*{q}")

if __name__ == '__main__':
    factors(sys.argv[1])

