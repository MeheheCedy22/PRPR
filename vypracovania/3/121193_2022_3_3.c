#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);
    int array[N];
    
    for (int i=0; i<N;i++)
    {
        scanf("%d",&array[i]);
    }

    int yes=1;

    if (array[0]>=0 && array[0]<=10)
    {
        for (int i=1; i<N;i++)
        {
            if(array[i]>(array[i-1]*2) || array[i]<(array[i-1]*0.5))
            {
                yes=0;
            }
        }
    }
    else
    {
        yes=0;
    }

    if (yes==1)
    {
        printf("\nPostupnost je spravna\n");
    }
    else if(yes==0)
    {
        printf("\nPostupnost nie je spravna\n");
    }
    else
    {
        printf("\nError\n");
    }

    return 0;
}