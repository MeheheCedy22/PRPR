#include <stdio.h>

int main()
{
    double num;
    scanf("%lf", &num);
    int a=num;
    printf("\n%d %.0lf\n", a, num);

    return 0;
}

//alternative with math.h library

/*

#include <stdio.h>
#include <math.h>

int main()
{
    double num;
    scanf("%lf", &num);
    int a=num;
    printf("\n%d %g\n", a, round(num));

    return 0;
}

*/