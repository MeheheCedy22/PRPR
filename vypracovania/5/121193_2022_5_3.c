#include <stdio.h>
#include <math.h>

int kvadraticka_rovnica(double a, double b, double c, double *x1, double *x2);

int main()
{
    double a, b, c, x1, x2;
    scanf("%lf %lf %lf", &a, &b, &c);
    
    if(a!=0)
    {
        printf("Pocet korenov kvadratickej rovnice %d\n", kvadraticka_rovnica(a, b, c, &x1, &x2));
        printf("Prvy koren ma hodnotu: %lf\n", x1);
        printf("Druhy koren ma hodnotu: %lf\n", x2);
    }
    else
    {
        printf("Nevieme delit nulou! (Rovnica by nebola kvadraticka)");
    }

    return 0;
}

int kvadraticka_rovnica(double a, double b, double c, double *x1, double *x2)
{
    double D;
    D=(pow(b, 2))-(4*a*c);

    if(D<0) //ziadny koren v R
    {
        printf("Diskriminant je zaporny, obor riesitelnosti je iba v komplexnych cislach (C).\n");
        
        return 0;
    }
    else if(D==0) //jeden koren
    {
        *x1=(-1*b)/(2*a);
        *x2=0;

        return 1;
    }
    else //dva korene
    {
        *x1=((-1*b)+sqrt(D))/(2*a); //sqrt(D) == pow(D, 0.5)
        *x2=((-1*b)-sqrt(D))/(2*a);

        return 2;
    }
}