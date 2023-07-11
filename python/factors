#!/usr/bin/python3

import sys
from concurrent.futures import ThreadPoolExecutor, as_completed
from math import gcd

def pollard_rho(n):
    x, y, c = 2, 2, 1
    while True:
        x = (x * x + c) % n
        y = (y * y + c) % n
        y = (y * y + c) % n
        d = gcd(abs(x - y), n)
        if d != 1:
            return d

def factorize(n):
    if n <= 3:
        return n, 1
    while True:
        d = pollard_rho(n)
        if d == n:
            continue
        return d, n // d

def process_number(line):
    n = int(line.strip())
    p, q = factorize(n)
    return f"{n}={p}*{q}"

if __name__ == "__main__":
    filename = sys.argv[1]
    with open(filename, "r") as f:
        with ThreadPoolExecutor(max_workers=16) as executor:
            futures = [executor.submit(process_number, line) for line in f]
            for future in as_completed(futures):
                print(future.result())

