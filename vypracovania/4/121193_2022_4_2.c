#include <stdio.h>

double tyzdenna_mzda(double h_mzda, double hod);

int main()
{
    int n;
    scanf("%d", &n);
    double m,h,spolu=0;

    for (int i=0; i<n; i++)
    {
        scanf("%lf %lf",&m,&h);
        printf("Hod. mzda: %.2lf Euro/hod, hodin: %.2lf, spolu: %.2lf Euro\n",m,h,tyzdenna_mzda(m,h));
        spolu+=tyzdenna_mzda(m,h);
    }

    printf("Celkova mzda: %.2lf Euro",spolu);

    return 0;
}

double tyzdenna_mzda(double h_mzda, double hod)
{
    return h_mzda*hod;
}