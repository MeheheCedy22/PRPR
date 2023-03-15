#include <stdio.h>

int main()
{
    int C1,C2;
    char ZNAK;
    scanf("%d %d %c", &C1, &C2, &ZNAK);
    if (ZNAK=='+')
    {
        printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1+C2);
    }
    if (ZNAK=='-')
    {
        printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1-C2);
    }
    if (ZNAK=='*')
    {
        printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1*C2);
    }
    if (ZNAK=='/')
    {
        printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1/C2);
    }

    return 0;
}