#include <stdio.h>

int main()
{
    int bezDPH;

    scanf("%d", &bezDPH);
    printf("\n");
    printf("Cena bez dane: %d\n", bezDPH);
    printf("Predajna cena s danou 20%%: %.1f\n", (bezDPH*1.2));

    return 0;
}