#include <stdio.h>

#define length 512 //tato konstanta predstavuje maximalnu dlzku suboru (nebola podmienka dynamickeho pola)
#define alphabet 26 //konstanta dlzk abecedy
#define diff 32 //rozdiel medzi 'a' a 'A' ak chcem z A na a tak pripocitam, ak naopak tak odpocitam

int main()
{
    char name[length]={0};
    char string_from_file[length]={0};
    int line_couunt=0;

    scanf("%s", &name);

    FILE *f;

    //otvori subor, ak sa nepodari tak vypise hlasku a ukonci program
    if((f=fopen(name,"r"))==NULL)
    {
        printf("Subor sa nepodarilo otvorit\n");
        return 0;
    }

    //vytlaci celu velku abecedu
    char c='A';
    printf("  ");
    for(int i=0; i<alphabet; i++)
    {
        printf("  %c", c);
        c++;
    }
    printf("\n");

    while((fgets(string_from_file, length, f))!=NULL) //do premenj string_from_file sa nacita cely riaodk ako string ale max dlzka je length zo subora f
    {
        printf("%2d", ++line_couunt); //tlaci cisla riadkov

        //deklaracia pola pre vyskyt pismen a jeho naplnenie nulami
        int pocty_vyskytov[alphabet];
        for(int i=0; i<alphabet; i++)
        {
            pocty_vyskytov[i]=0;
        }

        //prejde kazdy char nacitany v riadku ako string
        for(int i=0; i<length; i++)
        {
            //skonci ak najdeme '\0' alebo '\n' lebo vieme ze bud je koniec stringu alebo koniec riadku
            if(string_from_file[i]=='\n' || string_from_file[i]=='\0')
            {
                break;
            }

            //ak patri medzi A a Z alebo a a z tak pridame vyskyt na poziciu pismena v abecede
            if((string_from_file[i]>='a' && string_from_file[i]<='z') || (string_from_file[i]>='A' && string_from_file[i]<='Z'))
            {
                for(char ch='a'; ch<='z'; ch++)
                {
                    if(string_from_file[i]==ch || string_from_file[i]==ch-diff) //ak je to to iste alebo to iste len velke pisemno tak pripocitaj vyskyt
                        {
                            pocty_vyskytov[ch-'a']++;
                        }
                }
            }
        }

        //vyprintuje pocty vyskytov
        for(char i=0; i<alphabet; i++)
        {
            if(pocty_vyskytov[i]<100) //osetrenie aby bolo najviac dvojciferne cislo
            {
                printf(" %2d", pocty_vyskytov[i]);
            }
        }

        printf("\n");
    }
    

    fclose(f);

    return 0;
}