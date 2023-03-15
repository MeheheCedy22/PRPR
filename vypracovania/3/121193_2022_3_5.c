#include <stdio.h>


int main()
{
    int N=-1;
    unsigned long long int f=1;

    while(1)
    {
        scanf("%d", &N);
        if (N>=0)
        {
            break;
        }
    }

    for(int i=1;i<=N;i++)
    {
        
        f*=i;
    }

    printf("\n%llu",f);

    return 0;
}