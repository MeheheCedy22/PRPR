#include <stdio.h>

int main()
{
    float bezDPH;
    scanf("%f", &bezDPH);
    printf("\nCena bez dane: %f\n", bezDPH);
    printf("Predajna cena s danou 20%%: %.1f\n", (bezDPH*1.2));

    return 0;
}