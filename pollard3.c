#include <stdio.h>
#include <gmp.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: factors <file>\n");
        return (1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error: Can't open file %s\n", argv[1]);
        return (1);
    }

    mpz_t num, n, i, sqrt_n, rem;
    mpz_inits(num, n, i, sqrt_n, rem, NULL);
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
	mpz_set_str(num, line, 10);
        mpz_set_str(n, line, 10);
        mpz_sqrt(sqrt_n, n);

        if (mpz_even_p(n))
        {
            mpz_tdiv_q_ui(n, n, 2);
            gmp_printf("%Zd=%Zd*2\n", num, n);
	    continue;
        }

        if (mpz_divisible_ui_p(n, 3))
        {
            mpz_tdiv_q_ui(n, n, 3);
            gmp_printf("%Zd=%Zd*3\n", num, n);
	    continue;
        }

        for (mpz_set_ui(i, 5); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 6))
        {
            if (mpz_divisible_p(n, i))
            {
                mpz_tdiv_q(n, n, i);
                gmp_printf("%Zd=%Zd*%Zd\n", num, n, i);
                break;
            }
            mpz_add_ui(i, i, 2);
            if (mpz_divisible_p(n, i))
            {
                mpz_tdiv_q(n, n, i);
                gmp_printf("%Zd=%Zd*%Zd\n", num, n, i);
                break;
            }
        }
    }

    mpz_clears(n, i, sqrt_n, rem, NULL);
    fclose(fp);
    return (0);
}

