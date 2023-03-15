#include <stdio.h>

int main()
{
    int x[7]={4, 7, 1, 3, 2, 5, 6};
    int y[7];

    for(int i=0;i<7;i++)
    {
        y[i]=0;
        if(x[i]%2==0)
        {
            y[i]=x[i];

        }
        if(y[i]!=0)
        {
            printf("%d ", y[i]);
        }
    }

    return 0;
}