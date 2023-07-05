#!/usr/bin/python3
import sys
import random

def find_factor(n):
    # Check if n is 1
    if n == 1:
        return None
    # Check if n is even
    if n % 2 == 0:
        return 2
    # Check if n is prime
    if is_probably_prime(n):
        return None
    # Find a factor using Pollard's rho algorithm
    x = random.randint(1, n-1)
    c = random.randint(1, n-1)
    y, d, i = x, 1, 1
    while d == 1:
        x = (x**2 + c) % n
        y = (y**2 + c) % n
        y = (y**2 + c) % n
        d = gcd(abs(x-y), n)
        i += 1
        if i == 100:
            return None
    if d == n:
        return None
    else:
        return d

def is_probably_prime(n, k=10):
    # Miller-Rabin primality test
    if n <= 1:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False
    r, d = 0, n-1
    while d % 2 == 0:
        r += 1
        d //= 2
    for _ in range(k):
        a = random.randint(2, n-2)
        x = pow(a, d, n)
        if x == 1 or x == n-1:
            continue
        for _ in range(r-1):
            x = pow(x, 2, n)
            if x == n-1:
                break
        else:
            return False
    return True

def gcd(a, b):
    # Euclidean algorithm for finding the greatest common divisor
    while b:
        a, b = b, a % b
    return a

def factorize(n):
    # Find the first factor of n
    factor = find_factor(n)
    if factor is None or factor == n:
        return None
    # Find the second factor of n
    quotient = n // factor
    if quotient == n or quotient == 1:
        return None
    while quotient % 2 == 0:
        factor2 = 2
        quotient //= 2
    else:
        factor2 = n // factor
    if factor2 is None or factor2 == n or factor2 == 1:
        return f"{n}=1*{n}"
    # Return the factorization
    return f"{n}={factor}*{factor2}"

def main(filename):
    with open(filename, 'r') as f:
        for line in f:
            n = int(line.strip())
            factorization = factorize(n)
            print(factorization)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <file>")
        sys.exit(1)
    main(sys.argv[1])
