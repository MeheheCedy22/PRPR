#include <stdio.h>

int sum_digits(int x);

int main()
{
    int N;
    scanf("%d",&N);

    if(N>0)
    {
        printf("%d",sum_digits(N));
    }
    else
    {
        printf("Zadal si nekladne cislo");
    }

    return 0;
}

int sum_digits(int x)
{
    if(x>0)
    {
        return x%10+sum_digits(x/10); //posledna cifra + zavolaj_seba(cislo so zahodenou poslednou cifrou)
    }

    return 0;
}