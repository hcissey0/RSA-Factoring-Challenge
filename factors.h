#ifndef FACTORS_H
#define FACTORS_H

#include <gmp.h>

/**
 * struct pair_s - the pair of factors structure
 * @x: the first structure
 * @y: the second structure
 */
typedef struct pair_s
{
	mpz_t x;
	mpz_t y;
} pair;

#endif /* FACTORS_H */
