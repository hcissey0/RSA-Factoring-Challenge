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


        for (mpz_set_ui(i, 2); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 1))
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

