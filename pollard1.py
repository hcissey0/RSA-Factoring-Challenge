#!/usr/bin/python3
from math import gcd
from random import randint

def pollard_rho(n):
    x = y = c = randint(1, n - 1)
    g = 1
    while g == 1:
        x = (x * x + c) % n
        y = (y * y + c) % n
        y = (y * y + c) % n
        g = gcd(abs(x - y), n)
    return g

def factors(filename):
    with open(filename, 'r') as f:
        for line in f:
            n = int(line)
            if n <= 3:
                continue
            while True:
                factor = pollard_rho(n)
                if factor != n:
                    print(f"{n}={factor}*{n//factor}")
                    break

if __name__ == '__main__':
    import sys
    if len(sys.argv) != 2:
        print("Usage: factors <file>")
        sys.exit(1)
    factors(sys.argv[1])

