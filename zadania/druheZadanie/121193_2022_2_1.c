#include <stdio.h>

int main()
{
    float x,y,z;
    scanf("%f %f %f", &x, &y, &z);
    printf("\nPriemer cisel %g %g %g je: %g\n", x, y, z, ((x+y+z)/3));

    return 0;
}