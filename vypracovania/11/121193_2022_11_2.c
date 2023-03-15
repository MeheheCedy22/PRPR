/*zadanie si odporuje s príkladom*/

#include <stdio.h>

unsigned int invert(unsigned int x, int i, int n);

int main()
{
    unsigned int x, inverted;
    int i, n;

    printf("Zadajte cisla v nasledovnom tvare: \n");
    printf("cislo_ktore_chcete_invertovat index_pociatku kolko_bitov_chcete_invertovat\n");
    printf("x i n\n");
    scanf("%u%d%d", &x, &i, &n);

    inverted=invert(x, i, n);

    
    printf("Zadane cislo:\t   %15u (", x);
    for(int i=sizeof(unsigned int)*8-1; i>=0; i--)
    {
        printf("%d", (x>>i)&1);
    }
    printf(")\n");


    printf("Invertovane cislo: %15u (", inverted);
    for(int i=sizeof(unsigned int)*8-1; i>=0; i--)
    {
        printf("%d", (inverted>>i)&1);
    }
    printf(")\n");

    return 0;
}

unsigned int invert(unsigned int x, int i, int n)
{
    unsigned int inverted=x;
    unsigned int mask=0;

    for(int j=0; j<n; j++)
    {
        mask=mask<<1;
        mask=mask|1;
    }

    mask=mask<<(sizeof(unsigned int)*8-n-i);
    inverted=inverted^mask;

    return inverted;
}