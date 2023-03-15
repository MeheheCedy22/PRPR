#include <stdio.h>

int main()
{
    FILE *fr1, *fr2;
    char c, ch;
    int diff=0, x=0;

    if((fr1 = fopen("prvy.txt","r")) != NULL && (fr2 = fopen("druhy.txt","r")) != NULL)
    {
       while(1)
       {
            c = getc(fr1);
            ch = getc(fr2);

            if(c == EOF && ch == EOF)
            {
                break;
            }

            if(c == EOF || ch == EOF)
            {
                x++;
            }
            if(x == 0 && c != ch)
            {
                diff++;
            }
       }

       if(diff!=0)
       {
            printf("Pocet roznych znakov: %d\n", diff);
       }
       else
       {
            printf("Subory su identicke\n");
       }
       if(x!=0)
       {
            printf("Jeden zo suborov je dlhsi o %d znakov\n", x);
       }
    }
    else
    {
        printf("Subory sa nepodarilo otvorit\n");
    }

    fclose(fr1);
    fclose(fr2);

    return 0;
}