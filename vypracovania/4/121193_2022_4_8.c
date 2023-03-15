#include <stdio.h>

int main()
{
    FILE *fr;
    FILE *fw;
    char c, x;
    scanf("%c",&c);

    if(c=='s')
    {
        if((fr = fopen("znak.txt", "r")) != NULL && (fw = fopen("novy.txt", "w")) != NULL)
        {
            while((x = getc(fr)) != EOF) // zoberie znak a otestuje či nie je koniec suboru
            {
                ungetc(x, fr); //vrati znak z bufferu spat
                char n;
                fscanf(fr, "%c", &n);
                fprintf(fw, "%c", n);
            }
        }
        else
        {
            printf("Subor sa nepodarilo otvorit.\n");
        }
    }
    else
    {
        if((fr = fopen("znak.txt", "r")) != NULL)
        {
            while((x = getc(fr)) != EOF) // zoberie znak a otestuje či nie je koniec suboru
            {
                ungetc(x, fr); //vrati znak z bufferu spat
                char n;
                fscanf(fr, "%c", &n);
                printf("%c", n);
            }
        }
        else
        {
            printf("Subor sa nepodarilo otvorit.\n");
        }
    }

    fclose(fr);
    fclose(fw);

    return 0;
}