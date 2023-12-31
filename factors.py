#!/usr/bin/python3
import sys
from math import sqrt

def factorize(n):
    for i in range(2, int(n**0.5)+1):
        if n % i == 0:
            return (i, n//i)
    return None


def factors(n): 

    if n % 2 == 0:
        return n//2, 2
    if n % 3 == 0:
        return n//3, 3

    s = int(sqrt(n)) + 1
    i = 5
    while i <= s:
        if n % i == 0:
            return n//i , i
        i += 6
    for i in range(19, s):
        if n % i == 0:
            return n//i, i
    return None

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: factors <file>')
        sys.exit(1)

    with open(sys.argv[1], "r") as f:
        for line in f:
            n = int(line.strip())
            res = factors(n)
            if res is not None:
                print(f"{n}={res[0]}*{res[1]}")
