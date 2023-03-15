#include <stdio.h>

void vymen_ukazovatele(int **a, int **b);

int main()
{
    int a=10, b=14;
    int *ptr_a, *ptr_b;

    ptr_a=&a;
    ptr_b=&b;

    printf("p_a: %p %d\n", ptr_a, *ptr_a);
    printf("p_b: %p %d\n", ptr_b, *ptr_b);

    vymen_ukazovatele(&ptr_a, &ptr_b);

    printf("p_a: %p %d\n", ptr_a, *ptr_a);
    printf("p_b: %p %d\n", ptr_b, *ptr_b);

    return 0;
}

void vymen_ukazovatele(int **a, int **b)
{
    int *temp;
    temp=*a;
    *a=*b;
    *b=temp;
}