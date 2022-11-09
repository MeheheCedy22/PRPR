#include <stdio.h>
#include <stdlib.h>

void alokuj_2D_pole(int a, int b, int ***arr);
void vypis_2D_pole(int a, int b, int **arr);
void uvolni(int a, int ***arr);

int main()
{
    int n, m;
    int **arr;

    scanf("%d %d", &n, &m);

    if(n<0 || m<0)
    {
        printf("Treba zadat dve nezaporne cele cisla!\n");
        return 0;
    }

    alokuj_2D_pole(n, m, &arr);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf("%d", (*arr+i)+j);
        }
    }

    vypis_2D_pole(n, m, arr);
    uvolni(n, &arr);

    return 0;
}

void alokuj_2D_pole(int a, int b, int ***arr)
{
    *arr=(int**) calloc(a, sizeof(int*));

    for(int i=0; i<a; i++)
    {
        *(*arr+i)=(int*) calloc(b, sizeof(int));
    }
}

void vypis_2D_pole(int a, int b, int **arr)
{
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            printf("%d ", (*(*arr+i)+j));
        }
        printf("\n");
    }
}

void uvolni(int a, int ***arr)
{
    for(int i=0;i<a;i++)
    {
        free(*(*arr+i));
        *(*arr+i)=NULL;
    }

    free(*arr);
    *arr=NULL;
}