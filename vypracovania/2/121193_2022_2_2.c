#include <stdio.h>

//BMI=weight/(height*height) (-,kg,m)

int main()
{
    float w,h;
    scanf("%f %f", &h, &w);
    h/=100; //conversion cm -> m
    printf("\nBMI: %.3f\n",(w/(h*h)));

    return 0;
}