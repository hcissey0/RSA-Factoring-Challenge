#!/usr/bin/python3
import sys
from math import gcd
from random import randint
from concurrent.futures import ThreadPoolExecutor, as_completed

def brent_pollard_rho(n):
    y, c, m = randint(1, n-1), randint(1, n-1), randint(1, n-1)
    g, r, q = 1, 1, 1
    while g == 1:
        x = y
        for _ in range(r):
            y = (y * y + c) % n
        k = 0
        while k < r and g == 1:
            ys = y
            for _ in range(min(m, r-k)):
                y = (y * y + c) % n
                q = q * abs(x-y) % n
            g = gcd(q, n)
            k += m
        r *= 2
    if g == n:
        while True:
            ys = (ys * ys + c) % n
            g = gcd(abs(x - ys), n)
            if g > 1:
                break
    return g

def factorize(n):
    if n % 2 == 0:
        return n, 2, n // 2
    p = n
    while p == n:
        p = brent_pollard_rho(n)
    return n, p, n // p

if __name__ == '__main__':
    filename = sys.argv[1]
    numbers = []
    with open(filename, 'r') as f:
        for line in f:
            numbers.append(int(line.strip()))

    with ThreadPoolExecutor(16) as executor:
        futures = [executor.submit(factorize, n) for n in numbers]
        for future in as_completed(futures):
            n, p, q = future.result()
            print(f'{n}={p}*{q}')

