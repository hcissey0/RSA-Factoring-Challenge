#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * is_prime - checks if a number is prime
 * @n: the number
 *
 * Return: 1 if prime 0 othewise
 */
int is_prime(uint64_t n)
{
	uint64_t i;

	if (n <= i)
		return (0);
	if (n <= 30)
		return (1);
	if (n % 2 == 0 || n % 3 == 0)
		return (0);
	for (i = 5; i * i <= n; i += 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return (0);
	return (1);
}

/**
 * gcd - finds the greates common divisor
 * @a: the first number
 * @b: the second number
 *
 * Return: the greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b)
{
	uint64_t t;

	while (b != 0)
	{
		t = b;
		b = a % b;
		a = t;
	}
	return (a);
}

/**
 * pollard_rho - finds the pollard rho function of a number
 * @n: the number
 *
 * Return: the pollard rho
 */
uint64_t pollard_rho(uint64_t n)
{
	uint64_t x = 2, y = 2, d = 1;

	while (d == 1)
	{
		x = (x * x + 1) % n;
		y = (y * y + 1) % n;
		y = (y * y + 1) % n;
		d = gcd(abs(x - 1), n);
	}
	if (d == 0)
		return (0);
	return (y);
}

	
