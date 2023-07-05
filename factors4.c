#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void gcd(mpz_t rop, mpz_t a, mpz_t b) {
    mpz_t remainder;
    mpz_init(remainder);

    while (mpz_sgn(b) != 0) {
        mpz_mod(remainder, a, b);
        mpz_set(a, b);
        mpz_set(b, remainder);
    }

    mpz_set(rop, a);
    mpz_clear(remainder);
}

void f(mpz_t rop, mpz_t x, mpz_t c, mpz_t n) {
    mpz_mul(rop, x, x);
    mpz_add(rop, rop, c);
    mpz_mod(rop, rop, n);
}

void pollard_rho(mpz_t rop, mpz_t n) {
    if (mpz_even_p(n)) {
        mpz_set_ui(rop, 2);
        return;
    }

    gmp_randstate_t state;
    gmp_randinit_default(state);

    mpz_t x;
    mpz_init(x);
    mpz_urandomm(x, state, n);

    mpz_t y;
    mpz_init_set(y, x);

    mpz_t c;
    mpz_init(c);
    mpz_urandomm(c, state, n);

    mpz_t d;
    mpz_init_set_ui(d, 1);

    while (mpz_cmp_ui(d, 1) == 0) {
        f(x, x, c, n);
        f(y, y, c, n);
        f(y, y, c, n);
        mpz_sub(d, x, y);
        gcd(d, d, n);
        if (mpz_sgn(d) < 0)
            mpz_neg(d,d);
    }

    gmp_randclear(state);
    mpz_set(rop,d);

}

void factors(char *filename) {
    FILE *fp = fopen(filename,"r");
    
    if (fp == NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }
    
    char *line = NULL;
    size_t len = 0;
    
    while(getline(&line,&len ,fp)!= -1){
        line[strcspn(line,"\n")] = '\0';
        
        mpz_t n,p,q;
        
        mpz_init(n);
        mpz_init(p);
        mpz_init(q);
        
        if(mpz_set_str(n,line ,10)==-1){
            fprintf(stderr,"Error reading number\n");
            exit(1); 
        }
        
        pollard_rho(p,n);
        
        if(mpz_cmp_ui(p ,0)==0){
            printf("Error finding factor\n");
            exit(1); 
        }
        
        if(mpz_divisible_p(n,p)){
            printf("%s=",line); 
            mpz_divexact(q,n,p);
            gmp_printf("%Zd*%Zd\n",p ,q);
            
            }else{
                printf("Error finding factor\n");
                exit(1); 
            }
            
            }
            
            fclose(fp); 
            
}

int main(int argc,char **argv){
    
if(argc !=2){
fprintf(stderr,"Usage: factors <file>\n");
exit(1); 
}
factors(argv[1]); 

return 0; 
}

