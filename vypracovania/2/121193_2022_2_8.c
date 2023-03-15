#include <stdio.h>

int main()
{
    int a,b,c,d,e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    printf("\n%d\n", e/--a*b++/c++);

    /*
        Pri vstupe 6 2 2 4 5 je vysledok 1 pretože: inkrement a dekrement majú prednosť tz. najprv sa od premennej "a"
        odčíta 1 a hneď sa použija táto hodnota (kvôli prefixu) pri "b" a "c" sa použijú najprv hodnoty daných
        premenných a potom sa ku nim pričíta číslo 1, potom je postupnosť násobenia a delenia po rade zľava doprava
        ako v matematike. 5/(6-1)*2/2 = 5/5*2/2 = 1*2/2 = 2/2 = 1
    */

    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    printf("\n%d\n", a%=b=d=1+e/2);

    /*
        Pri vstupe 6 2 2 4 5 je vysledok 0 pretože: najprv sa vypočíta čomu sa dovná premenná "d" pretože priradenie je zprava doľava
        takže to bude d=1+5/2 = 1+2 = 3 , takže hodnota premennej "d" sa zmení zo 4 na 3, potom sa premenná "d" priradí
        do premennej "b" a ostane nám výraz a%=b ktorý môžeme napísať ako a=a%b a ten vypočítame nasledovne a=6%3 = 0
    */

    return 0;
}