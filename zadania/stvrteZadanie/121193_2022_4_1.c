//vyriesil som to takto lebo som nechcel pouzit algoritmus z webu aj ked toto riesenie je oproti internetovemu dost neefektivne
//pocital som s tym ze interval je otvoreny
#include <stdio.h>

int zisti_prvocislo(int cislo);

int main()
{
    int bottom,top;
    scanf("%d %d", &bottom,&top);

    if ((bottom<top && 0<top) && (bottom+1<top && 0<top)) //druha cast podmienky je tam kvoli tomu ked mame napr interval (4;5) tak medzi tym nie je ani jedno cele cislo
    {
        for(int i=bottom+1; i<top; i++) //plati pre otvoreny interval
        {
            if(zisti_prvocislo(i)==1)
            {
                printf("%d\n",i);
            }
        }
    }
    else
    {
        printf("Prvocislo neexistuje\n");
    }

    return 0;
}

int zisti_prvocislo(int cislo)
{
    if(cislo == 2 || cislo == 3 || cislo==5 || cislo==7) //vypisem prve cifry ktore su prvocisla aby nepocitalo do dalsich podmienok
    {
        return 1;
    }
    if(cislo<=1 || cislo%2==0 || cislo%3==0 || cislo%5==0 || cislo%7==0) //4,6,8 mozeme preskocit pretoze cisla ktore su delitelne tymito ciframi su delitelne dvojkou lebo su parne, preskocime aj 9 pretoze vsetky delitelne 9 su aj trojkou
    {
        return -1;
    }

    //posledny krok je otestovat delitelnost nejakeho cisla prvocislom napr 11*11=121 ->121 nie je prvocislo
    int isPrime;

    for (int i=11; i<cislo; i++) //staci zacinat od 11 pretoze ostatne uz mam vybavene
	{
		isPrime=1;

        for (int j=2; j<=cislo/2; j++) //staci do polovice toho cisla lebo ak by bolo viacej tak uz to je pod delitelnost dvojky a tam uz su iba desatinne cisla alebo jednotka a ani jedno by neplatilo potom pre prvocislo
		{
            if (cislo%j==0)
			{
                isPrime=0;
            }
        }
        
        if (isPrime==1)
        {
            return 1;
		}
        else if(isPrime==0)
        {
            return -1;
        }
    }

    return 1;
}