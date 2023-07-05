#!/usr/bin/python3
import sys
import math
from sympy import isprime, nextprime
from concurrent.futures import ThreadPoolExecutor, as_completed

def tonelli_shanks(n, p):
    assert pow(n, (p - 1) // 2, p) == 1
    Q = p - 1
    S = 0
    while Q % 2 == 0:
        Q //= 2
        S += 1
    if S == 1:
        return pow(n, (p + 1) // 4, p)
    for z in range(2, p):
        if p - 1 == pow(z, (p - 1) // 2, p):
            break
    c = pow(z, Q, p)
    R = pow(n, (Q + 1) // 2, p)
    t = pow(n, Q, p)
    M = S
    while (t - 1) % p != 0:
        for i in range(1, M):
            if (pow(t, (1 << i), p) - 1) % p == 0:
                break
        b = pow(c, (1 << (M - i - 1)), p)
        R = (R * b) % p
        t = (t * b * b) % p
        c = (b * b) % p
        M = i
    return R

def legendre_symbol(a, p):
    ls = pow(a, (p - 1) // 2, p)
    return -1 if ls == p - 1 else ls

def sieve_of_eratosthenes(n):
    prime = [True for _ in range(n + 1)]
    prime[0] = prime[1] = False
    for i in range(2, int(math.sqrt(n)) + 1):
        if prime[i]:
            for j in range(i * i, n + 1, i):
                prime[j] = False
    primes = []
    for i in range(2, n + 1):
        if prime[i]:
            primes.append(i)
    return primes

def find_factor(base_array, smooth_relations):
    exponent_matrix = []
    for factors in smooth_relations:
        exponents = [0] * len(base_array)
        for prime_index, power in factors:
            exponents[prime_index] += power % 2
        exponent_matrix.append(exponents)

    nullspace = find_nullspace(exponent_matrix)

    for nullspace_row in nullspace:
        x = y = 1
        for index in range(len(nullspace_row)):
            if nullspace_row[index] == 0:
                continue
            x *= smooth_relations[index][0]
            y *= smooth_relations[index][0]**2 // smooth_relations[index][1]
        x %= n
        y = int(gmpy2.sqrt(y)) % n

        factor = math.gcd(x - y, n)
        if factor != 1 and factor != n:
            return factor

def find_nullspace(m):
    rows = len(m)
    cols = len(m[0])
    
    nullspace = []
    
    for col in range(cols):
        free_var_index_set = set(range(rows))
        
        row_op_count = col
        
        for row_op in range(row_op_count):
            pivot_row_index = None
            
            for row_index in free_var_index_set:
                if m[row_index][row_op] == 1:
                    pivot_row_index = row_index
                    break
            
            if pivot_row_index is None:
                continue
            
            free_var_index_set.remove(pivot_row_index)
            
            if m[pivot_row_index][col] == 0:
                continue
            
            for row_index in free_var_index_set:
                if m[row_index][col] == 0:
                    continue
                
                for j in range(row_op_count + 1):
                    m[row_index][j] ^= m[pivot_row_index][j]
        
        free_var_vector = [0] * cols
        
        free_var_vector[col] = 1
        
        for row_op in reversed(range(row_op_count)):
            pivot_row_index = None
            
            for row_index in range(rows):
                if m[row_index][row_op] == 0 or row_index in free_var_index_set:
                    continue
                
                pivot_row_index = row_index
                
                break
            
            if pivot_row_index is None or free_var_vector[row_op] == 0:
                continue
            
            free_var_vector[col] ^= m[pivot_row_index][col]
        
        nullspace.append(free_var_vector)
    
    return nullspace

def find_smooth_relations(factor_base, n, sieve_array_size):
    smooth_relations = []
    perfect_powers = []
    target = len(factor_base) + 5
    x = 1
    while len(smooth_relations) < target:
        smooth_num = (x * x) % n
        smooth_num_copy = smooth_num
        factors = []
        for i in range(len(factor_base)):
            if smooth_num % factor_base[i] == 0:
                count = 0
                while smooth_num % factor_base[i] == 0:
                    count += 1
                    smooth_num //= factor_base[i]
                factors.append((i, count))
        if smooth_num == 1:
            smooth_relations.append((x, smooth_num_copy, factors))
        elif legendre_symbol(smooth_num, n) == 1:
            perfect_powers.append((x, smooth_num))
        x += 1

    perfect_powers_copy = perfect_powers.copy()
    for x, value in perfect_powers:
        for y, value2 in perfect_powers_copy:
            if value == value2 and x != y:
                factors = []
                for i in range(len(factor_base)):
                    if value % factor_base[i] == 0:
                        count = 0
                        while value % factor_base[i] == 0:
                            count += 1
                            value //= factor_base[i]
                        factors.append((i, count))
                if value == 1:
                    smooth_relations.append((x * y, (x * x * y * y) % n, factors))
                    break

    return smooth_relations[:target]

def quadratic_sieve(n):
    if n % 2 == 0:
        return n // 2
    if isprime(n):
        return n

    root_n = math.isqrt(n)
    root_2n = math.isqrt(n * 2)

    bound = math.exp(math.sqrt(math.log(n) * math.log(math.log(n)))) // 2
    prime_factors = sieve_of_eratosthenes(int(bound))

    prime_factors_index = {prime: i for i, prime in enumerate(prime_factors)}

    factor_base = []

    for p in prime_factors:
        if legendre_symbol(n, p) == 1:
            factor_base.append(p)

    sieve_array_size = len(factor_base) * 10

    smooth_relations = find_smooth_relations(factor_base, n, sieve_array_size)

    factor_base_index = {factor: index for index, factor in enumerate(factor_base)}

    while True:
        x_y_values = []
        for _, b_value, factors in smooth_relations:
            x_y_values.append((b_value, reduce(lambda a, b: a * b[0]**(b[1] // 2), factors, 1)))

        a_values = [a for a, _ in x_y_values]
        b_values = [b for _, b in x_y_values]

        a_value_product = reduce(lambda a, b: a * b % n, a_values)
        b_value_product = reduce(lambda a, b: a * b % n, b_values)

        gcd_value = math.gcd(a_value_product - b_value_product, n)

        if gcd_value != 1 and gcd_value != n:
            return gcd_value

def factorize(n):
    if n % 2 == 0:
        return n // 2
    p = quadratic_sieve(n)
    return p

if __name__ == '__main__':
    filename = sys.argv[1]
    numbers = []
    with open(filename, 'r') as f:
        for line in f:
            numbers.append(int(line.strip()))

    with ThreadPoolExecutor() as executor:
        futures = [executor.submit(factorize, n) for n in numbers]
        for future in as_completed(futures):
            p = future.result()
            q = numbers.pop(0) // p
            print(f'{p*q}={p}*{q}')

