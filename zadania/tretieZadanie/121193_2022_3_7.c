#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    if(N>=1 && N<=15)
    {
        for(int i=0;i<N;i++)
        {
            printf("\n%d: ",i+1);
            for(int j=N-i;j>0;j--)
            {
                printf("%d ",j);
            }
        }
    }
    else
    {
        printf("Cislo nie je z daneho intervalu");
    }

    return 0;
}