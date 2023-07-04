#include <stdio.h>
#include <gmp.h>

int main(int ac, char **av)
{
	FILE *fp;
	mpz_t num, n, i, sqrt_n, rem;
	char line[1024];

	if (ac != 2)
	{
		printf("Usage: factors <file>\n");
		return (1);
	}
	fp = fopen(av[1], "r");
	if (fp == NULL)
	{
		printf("Error: Can't open file %s\n", av[1]);
		return (1);
	}

	mpz_inits(num, n, i, sqrt_n, rem, NULL);
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		mpz_set_str(num, line, 10);
		mpz_set_str(n, line, 10);
		mpz_sqrt(sqrt_n, n);

		mpz_tdiv_r_ui(rem, n, 2);
		if (mpz_cmp_ui(rem, 0) == 0)
		{
			mpz_tdiv_q_ui(n, n, 2);
			gmp_printf("%Zd=%Zd*2\n", n, n);
			continue;
		}
		for (mpz_set_ui(i, 3); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 2))
		{
			mpz_tdiv_r(rem, n, i);
			if (mpz_cmp_ui(rem, 0) == 0)
			{
				mpz_tdiv_q(n, n, i);
				gmp_printf("%Zd=%Zd*%Zd\n", num, n, i);
				break;
			}
		}
	}
	mpz_clears(num, n, i, sqrt_n, rem, NULL);
	fclose(fp);
	return (0);
}
