#include <stdio.h>
#include <stdlib.h> //maloc

void alokuj_1D_pole(int x, int **p_x);
void vypis_1D_pole(int y, int *p_y);
int maximum_poz(int z, int *p_z);
int minimum_poz(int w, int *p_w);
void uvolni(int *p);

int main()
{
    int m;
    int *p_m;

    scanf("%d", &m);

    if(m>0)
    {
        alokuj_1D_pole(m, &p_m);
        vypis_1D_pole(m, p_m);
        printf("\nMax: %d\n", maximum_poz(m, p_m));
        printf("Min: %d\n", minimum_poz(m, p_m));
        uvolni(p_m);
    }

    return 0;
}

void alokuj_1D_pole(int x, int **p_x)
{
    if((*p_x = (int *) malloc(x * sizeof(int)))!=NULL)
    {
        for(int i=0; i<x; i++)
        {
            scanf("%d", ((*p_x)+i));
        }
    }
}

void vypis_1D_pole(int y, int *p_y)
{
    for(int i=0; i<y; i++)
    {
        printf("%d,", p_y[i]);
    }
}

int maximum_poz(int z, int *p_z)
{
    for (int i = 1; i < z; i++)
    {
        if (*p_z < *(p_z + i))
        *p_z = *(p_z + i);    
    }
    return *p_z;
}

int minimum_poz(int w, int *p_w)
{
    for (int i = 1; i < w; i++)
    {
        if (*p_w > *(p_w + i))
        *p_w = *(p_w + i);    
    }
    return *p_w;
}

void uvolni(int *p)
{
    free(p);
}