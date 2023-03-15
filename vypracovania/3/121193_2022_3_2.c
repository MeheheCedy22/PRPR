#include <stdio.h>

int main()
{
    int N;
    float min,max;
    scanf("%d",&N);
    float array[N];
    
    for (int i=0;i<N;i++)
    {
        scanf("%f",&array[i]);
    }

    min=max=array[0];

    for (int j=0;j<N;j++)
    {
        if(min>array[j])
        {
            min=array[j];
        }
        if(max<array[j])
        {
            max=array[j];
        }
    }

    printf("\nMinimum: %.2f\n",min);
    printf("\nMaximum: %.2f\n",max);

    return 0;
}