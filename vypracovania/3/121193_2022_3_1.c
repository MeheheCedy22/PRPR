#include <stdio.h>

int main()
{
    int C1,C2;
    char ZNAK;
    scanf("%d %d %c", &C1, &C2, &ZNAK);
    switch(ZNAK)
    {
        case '+':
            printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1+C2);
            break;
        case '-':
            printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1-C2);
            break;
        case '*':
            printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1*C2);
            break;
        case '/':
            printf("\n%d %c %d = %d\n", C1, ZNAK, C2, C1/C2);
            break;
        default:
            printf("Zle zadana volba");
    }
    
    return 0;
}