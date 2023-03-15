#include <stdio.h>

int main()
{
    FILE *fr;
    char c;
    float sum=0;

    if((fr = fopen("cisla.txt", "r")) == NULL)
    {
        printf("Neexistuje subor: cisla.txt.\n");
    }
    else
    {
        while((c = getc(fr)) != EOF) // zoberie znak a otestuje či nie je koniec suboru
        {
            ungetc(c,fr); //vrati znak z bufferu spat
            float n;
            fscanf(fr, "%f", &n);
            printf("%.2f\n", n);
            sum+=n;
        }
        printf("Sucet cisel je: %.2f", sum);
    }

    fclose(fr);

    return 0;
}