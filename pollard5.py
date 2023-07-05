#!/usr/bin/python3
import random

def pollard_rho(n):
  p = 2
  q = 1
  while p * q != n and gcd(p, n) != 1 and gcd(q, n) != 1:
    y = random.randrange(2, n - 1)
    p = pow(y, pow(y, n - 1, n), n)
    q = pow(y, p, n)
  return p, q

def gcd(a, b):
  while b != 0:
    a, b = b, a % b
  return a

def main():
  n = int(input("Enter a number: "))
  p, q = pollard_rho(n)
  print(f"{n} = {p} * {q}")

if __name__ == "__main__":
  main()

