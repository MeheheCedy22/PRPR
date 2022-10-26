#include <stdio.h>

void nacitaj(float *x, float *y);
void vypocitaj(float x, float y, float *S, float *O);

int main()
{
    float a, b, obsah, obvod;
    nacitaj(&a, &b);
    vypocitaj(a, b, &obsah, &obvod);

    printf("Obsah: %.3f\n", obsah);
    printf("Obvod: %.3f\n", obvod);

    return 0;
}

void nacitaj(float *x, float *y)
{
    scanf("%f %f", x, y); //uz netreba adresu pretoze uz ukazujeme na adresu
}

void vypocitaj(float x, float y, float *S, float *O)
{
    *S=x*y;
    *O=2*(x+y);
}