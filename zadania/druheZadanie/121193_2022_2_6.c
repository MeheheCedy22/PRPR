#include <stdio.h>

int main()
{
    int C1,C2;
    scanf("%d %d", &C1, &C2);
    if(C1>C2)
    {
        printf("\nCislo C1=%d je vacsie ako C2=%d.\n", C1, C2);
    }
    else
    {
        printf("\nCislo C1=%d je mensie ako C2=%d.\n", C1, C2);
    }

    return 0;
}