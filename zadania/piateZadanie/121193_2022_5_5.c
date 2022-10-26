#include <stdio.h>

#define N 10 //N nastav pre velkost statickeho pola

int delitele(int x[], int pocetx, int y[], int k);

int main()
{
    int arr_x[N]={4, 7, 10, 2, 3, 9, 6, 5, 8, 12};
    int arr_y[N];
    int pocety;

    pocety=delitele(arr_x, N, arr_y, 24);

    printf("\npocety: %d\n", pocety);

    return 0;
}

int delitele(int x[], int pocetx, int y[], int k)
{
    int count=0;
    for(int i=0; i<pocetx; i++)
    {
        if(k%x[i]==0)
        {
            y[i]=x[i];
            printf("%d ", y[i]);
            count++;
        }
    }
    
    return count;
}