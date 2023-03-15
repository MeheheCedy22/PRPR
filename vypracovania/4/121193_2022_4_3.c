#include <stdio.h>

long reverzne_cislo(long x);

int main()
{
    long num;
    while(scanf("%ld",&num)==1) //bude nacitavat hodnoty stale pretoze ak nieco scanf nacita tak navratova hodnota je 1
    {
        if(num>0)
        {
            printf("%ld\n",reverzne_cislo(num));
        
            if(num==reverzne_cislo(num))
            {
                printf("Cislo %ld je palindrom\n",num);
            }
            else
            {
                printf("Cislo %ld nie je palindrom\n",num);
            }
        }
        else
        {
            printf("Zaporne cislo nikdy nie je palindrom\n");
        }
    }

    return 0;
}

long reverzne_cislo(long x)
{
    long sum=0,temp;
    temp=x;

    while(x>0)
    {
        temp=x%10; //v podstate zoberie poslednu cifru
        sum=(sum*10)+temp; //cifru ktoru zobralo zacne davat od zaciatku
        x=x/10; //zahodi poslednu cifru
    }

    return sum;
}