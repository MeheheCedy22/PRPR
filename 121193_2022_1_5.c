#include <stdio.h>

int main()
{
    float PI=3.14;
    int r;
    
    scanf("%d", &r);
    printf("Obvod kruhu s polomerom %d je: %f\n", r, (2*PI*r));
    
    return 0;
}