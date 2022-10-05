#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);
    printf("\n");
    float array[N];
    
    for (int i=0; i<N;i++)
    {
        scanf("%f",&array[i]);
    }

    if (array[0]>=0 && array[0]<=10)
    {
        for (int i=0; i<N;i++)
        {
            if(array[i]>1 && array[i]<=(2*array[i-1]) && array[i]>=(array[i-1]*0.5))
            {
                printf("\nPostuponost je spravna\n");
                break;
            }
            else
            {
                printf("\nPostupnost nie je spravna\n");
                break;
            }
        }
    }
    else
    {
        printf("\nPostupnost nie je spravna\n");
    }

    return 0;
}