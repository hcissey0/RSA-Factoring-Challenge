#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

// Pollard's Rho function
void pollards_rho(mpz_t factor, const mpz_t n) {
  mpz_t x, y, divisor, tmp;
  mpz_inits(x, y, divisor, tmp, NULL);

  gmp_randstate_t state;
  gmp_randinit_default(state);
  gmp_randseed_ui(state, time(NULL));

  mpz_urandomm(x, state, n);
  mpz_set(y, x);
  mpz_set_ui(divisor, 1);

  while (mpz_cmp_ui(divisor, 1) == 0) {
    mpz_mul(x, x, x);
    mpz_mod(x, x, n);
    mpz_add_ui(x, x, 1);

    mpz_mul(y, y, y);
    mpz_mod(y, y, n);
    mpz_add_ui(y, y, 1);

    mpz_mul(y, y, y);
    mpz_mod(y, y, n);
    mpz_add_ui(y, y, 1);

    mpz_sub(tmp, x, y);
    mpz_abs(tmp, tmp);
    mpz_gcd(divisor, tmp, n);
  }

  mpz_set(factor, divisor);
  mpz_clears(x, y, divisor, tmp, NULL);
  gmp_randclear(state);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: factors <file>\n");
    return (1);
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Error: Can't open file %s\n", argv[1]);
    return (1);
  }

  mpz_t num, n, factor;
  mpz_inits(num, n, factor, NULL);
  char line[1024];
  while (fgets(line, sizeof(line), fp) != NULL) {
    mpz_set_str(num, line, 10);
    mpz_set_str(n, line, 10);

    if (mpz_even_p(n)) {
      mpz_tdiv_q_ui(n, n, 2);
      gmp_printf("%Zd=%Zd*2\n", num, n);
      continue;
    }

    if (mpz_divisible_ui_p(n, 3)) {
      mpz_tdiv_q_ui(n, n, 3);
      gmp_printf("%Zd=%Zd*3\n", num, n);
      continue;
    }

    pollards_rho(factor, n);
    if (mpz_cmp_ui(factor, 1) > 0 && mpz_cmp(factor, n) < 0) {
      mpz_tdiv_q(n, n, factor);
      gmp_printf("%Zd=%Zd*%Zd\n", num, n, factor);
    }
  }

  mpz_clears(num, n, factor, NULL);
  fclose(fp);
  return (0);
}
