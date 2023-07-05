#!/usr/bin/python3
import sys
from math import gcd
from random import randint
from concurrent.futures import ThreadPoolExecutor, as_completed

def pollard_rho(n):
    x = randint(2, n - 1)
    y = x
    c = randint(1, n - 1)
    g = 1
    while g == 1:
        x = (x * x + c) % n
        y = (y * y + c) % n
        y = (y * y + c) % n
        g = gcd(abs(x - y), n)
    return g

def factorize(n):
    if n % 2 == 0:
        return n, 2, n // 2
    p = n
    while p == n:
        p = pollard_rho(n)
    return n, p, n // p

if __name__ == '__main__':
    filename = sys.argv[1]
    numbers = []
    with open(filename, 'r') as f:
        for line in f:
            numbers.append(int(line.strip()))

    with ThreadPoolExecutor() as executor:
        futures = [executor.submit(factorize, n) for n in numbers]
        for future in as_completed(futures):
            n, p, q = future.result()
            print(f'{n}={p}*{q}')

