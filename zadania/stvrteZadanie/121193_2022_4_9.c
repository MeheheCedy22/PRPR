#include <stdio.h>

int main()
{
    FILE *fr;
    char c;
    int space=0;

    if((fr = fopen("text.txt","r")) != NULL)
    {
        while((c = getc(fr)) != EOF) // zoberie znak a otestuje či nie je koniec suboru, potom staci c lebo uz ten char zobral
        {
            if(c=='*')
            {
                printf("Koniec\n");
                break;
            }

            switch (c)
            {
                case 'x':
                case 'X':
                    printf("Precital som X\n");
                    break;
                case 'y':
                case 'Y':
                    printf("Precital som Y\n");
                    break;
                case '#':
                case '$':
                case '&':
                    printf("Precital som riadiaci znak\n");
                    break;
                case ' ':
                    space++;
                    break;
                default:;
            }
        }

        printf("Pocet precitanych medzier: %d\n", space);
    }
    else
    {
        printf("Subor sa nepodarilo otvorit");
    }
    
    fclose(fr);

    return 0;
}