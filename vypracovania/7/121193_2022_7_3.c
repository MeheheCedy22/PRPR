#include <stdio.h>

#define N 20 //konstanta pre zmenu statickeho pola

int magicky(int loc_arr[N][N], int n);

int main()
{
    int arr[N][N]={0};
    int n;

    scanf("%d", &n);

    if(n>N)
    {
        printf("Zadaj mensie n pretoze rozmer pola je %d x %d\n", N, N);
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    if(magicky(arr, n)==1)
    {
        printf("Stvorec je magicky\n");
    }
    else if (magicky(arr, n)==0)
    {
        printf("Stvorec nie je magicky\n");
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}

int magicky(int loc_arr[N][N], int n)
{
    int uhl1=0, uhl2=0;

    //overujem najprv ulhopriecky (vzdy 2)
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j)
            {
                uhl1+=loc_arr[i][j];
            }

            if(n-1==i+j)
            {
                uhl2+=loc_arr[i][j];
            }
        }
    }

    if(uhl1!=uhl2)
    {
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        int riad=0, stlp=0;
        for(int j=0; j<n; j++)
        {
            riad+=loc_arr[i][j];
            stlp+=loc_arr[j][i];
        }

        if(riad!=stlp || riad!=uhl1)
        {
            return 0;
        }
    }

    return 1;
}