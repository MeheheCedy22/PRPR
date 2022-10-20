#include <stdio.h>

int main()
{
    FILE *fw;    
    float x;
    scanf("%f", &x);

    if((fw = fopen("nasobky.txt", "w")) == NULL)
    {
        printf("Subor sa nepodarilo otvorit.\n");
    }
    else
    {
        for(int i=1; i<=10; i++)
        {
            fprintf(fw,"%2d * %.2f = %.2f\n", i, x, i*x);
        }
    }

    fclose(fw);

    return 0;
}