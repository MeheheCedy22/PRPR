#include <stdio.h>

int maximum(int *x, int *y);

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);

    if(maximum(&a, &b)!=0) //osetrene keby zada dve rovnake cisla
    {
        printf("Cislo %d je vacsie.", maximum(&a, &b));
    }
    else
    {
        printf("Cisla su zhodne!");
    }

    return 0;
}

int maximum(int *x, int *y)
{
    if(*x>*y)
    {
        return *x;
    }
    else if(*x<*y)
    {
        return *y;
    }
    else
    {
        return 0;
    }
}