#include <stdio.h>
#include <gmp.h>

void pollard_rho(mpz_t n, mpz_t p, mpz_t q);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: factors <file>\n");
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Could not open file %s\n", argv[1]);
    return 1;
  }

  mpz_t n;
  mpz_init(n);

  while (fscanf(fp, "%Zd\n", n) != EOF) {
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    // Use the Pollard Rho algorithm to factor n.
    pollard_rho(n, p, q);

    // Print the factorization.
    printf("%Zd=%Zd*%Zd\n", n, p, q);

    mpz_clear(p);
    mpz_clear(q);
  }

  fclose(fp);

  return 0;
}

void pollard_rho(mpz_t n, mpz_t p, mpz_t q) {
  // Initialize p and q to 2 and 1.
  mpz_set_ui(p, 2);
  mpz_set_ui(q, 1);

  // While p and q are relatively prime to n, keep iterating.
  while (mpz_gcd(p, n) != 1 || mpz_gcd(q, n) != 1) {
    // Generate a random number y between 2 and n-1.
    mpz_t y;
    mpz_init(y);
    mpz_randrange(y, 2, n-1);

    // Set p to the result of the Pollard Rho iteration.
    mpz_powm(p, y, y, n);
    mpz_gcd(p, n, p);

    // Set q to the result of the Pollard Rho iteration.
    mpz_powm(q, y, p, n);
    mpz_gcd(q, n, q);
  }
}

