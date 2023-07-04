#include <stdio.h>
#include <gmp.h>
#include <time.h>

void pollard_rho(mpz_t factor, const mpz_t n)
{
    mpz_t x, y, c, g;
    mpz_inits(x, y, c, g, NULL);
    mpz_set_ui(x, 2);
    mpz_set_ui(y, 2);
    mpz_set_ui(c, 1);

    do
    {
        mpz_mul(x, x, x);
        mpz_add(x, x, c);
        mpz_mod(x, x, n);

        mpz_mul(y, y, y);
        mpz_add(y, y, c);
        mpz_mod(y, y, n);

        mpz_mul(y, y, y);
        mpz_add(y, y, c);
        mpz_mod(y, y, n);

        mpz_sub(g,x,y);
        mpz_abs(g,g);
        mpz_gcd(g,g,n);
    } while(mpz_cmp_ui(g,1)==0);

    if(mpz_cmp(g,n)!=0)
        mpz_set(factor,g);

    mpz_clears(x,y,c,g,NULL);
}

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("Usage: factors <file>\n");
        return(1);
    }

    FILE *fp=fopen(argv[1],"r");
    if(fp==NULL)
    {
        printf("Error: Can't open file %s\n",argv[1]);
        return(1);
    }

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state,time(NULL));

    char line[1024];
    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        mpz_t n;
        mpz_init_set_str(n,line,10);

        if(mpz_probab_prime_p(n,10))
            continue;

        while(1)
        {
            mpz_t factor;
            mpz_init(factor);

            pollard_rho(factor,n);

            if(mpz_cmp_ui(factor,0)!=0)
            {
                mpz_t q;
                mpz_init(q);
                mpz_tdiv_q(q,n,factor);

                gmp_printf("%Zd=%Zd*%Zd\n",n,factor,q);
                break;
            }

            mpz_clear(factor);
        }

        mpz_clear(n);
    }

    fclose(fp);
    gmp_randclear(state);
    return(0);
}

