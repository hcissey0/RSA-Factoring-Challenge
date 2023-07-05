#!/usr/bin/python3
from math import gcd
import random
import sys

def pollard_rho(n):
    if n % 2 == 0:
        return 2
    x = random.randint(1, n - 1)
    y = x
    c = random.randint(1, n - 1)
    g = 1
    while g == 1:
        x = ((x * x) % n + c) % n
        y = ((y * y) % n + c) % n
        y = ((y * y) % n + c) % n
        g = gcd(abs(x - y), n)
    return g

def factors(filename):
    with open(filename, 'r') as f:
        for line in f:
            n = int(line.strip())
            p = pollard_rho(n)
            print(f"{n}={p}*{n//p}")

if __name__ == '__main__':
    factors(sys.argv[1])

