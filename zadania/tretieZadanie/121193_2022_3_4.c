#include <stdio.h>

int main()
{
    int N,in=0;
    scanf("%d", &N);
    printf("\n");
    int array[N];
    
    for (int i=0; i<N;i++)
    {
        scanf("%d",&array[i]);
    }
    
    for (int i=0; i<N;i++)
    {
        if(array[i]>0 && array[i]<=100)
        {
            in++;
        }
    }

    printf("\n%d\n",in);

    return 0;
}