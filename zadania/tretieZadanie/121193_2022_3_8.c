#include <stdio.h>

int main()
{
    int N;
    scanf("%d",&N);

    if(N>=1 && N<=15 && N%2!=0)
    {
        for(int i=0;i<N;i++)
        {
            for (int j=0;j<N;j++)
            {
                if(j==N/2 || i==N/2 || i==j || j+i==N-1)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("Zly vstup");
    }

    return 0;
}