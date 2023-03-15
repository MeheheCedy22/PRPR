#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define name_len 20

typedef struct tovar
{
    char nazov[name_len]; //dlzka mena je max 20 znakov
    char vyrobca[name_len];
    int pocet_kusov;
    int jednot_cena;

} TOVAR;

void vypis(TOVAR *tovar, int length);
void add(TOVAR **tovar, int *length);

int main()
{
    int n=0; //velkost pola
    int input;
    int end=0;

    TOVAR *tovar=(TOVAR*)calloc(1, sizeof(TOVAR));

    printf("\n0 - ukonci program, 1 - vypis, 2 - pridanie do zoznamu\n");

    while(1)
    {
        printf("Zadajte cislo pre operaciu: \n");
        
        scanf("%d", &input);

        switch(input)
        {
            case 2:
                add(&tovar, &n);
                break;
            case 1:
                vypis(tovar, n);
                break;
            case 0:
                end=1;
                break;
            default:
                printf("Zadal si zly vstup!\n");
                break;
        }
        if(end)
        {
            break;
        }
    }

    free(tovar);
    tovar=NULL;

    return 0;
}

void vypis(TOVAR *tovar, int length)
{
    printf("\nvypis\n\n");
    for(int i=0; i<length; i++)
    {
        printf("Polozka c.%d: \n",i+1);
        printf("Nazov tovaru: %s\n", tovar[i].nazov);
        printf("Nazov vyrobcu: %s\n", tovar[i].vyrobca);
        printf("Pocet kusov: %d\n", tovar[i].pocet_kusov);
        printf("Jednotkova cena: %d\n", tovar[i].jednot_cena);
    }
}

void add(TOVAR **tovar, int *length)
{
    //temp premenne
    char nazov[name_len];
    char vyrobca[name_len];
    int pocet_kusov;
    int jednot_cena;

    printf("Zadajte tovar v nasledujucom tvare: \n");
    printf("Nazov pocet_kusov vyrobca jednotkova_cena\n");

    scanf("%s%d%s%d", nazov, &pocet_kusov, vyrobca, &jednot_cena);

    int i=0;
    while((i<*length) && (strcmp(nazov, (*tovar)[i].nazov)>0)) //porovnam ktory je skorej v abecede, ak > 0 znamena ze string2 je mensi ako string1 a to znamena ze je skorej v abecede
    {
        i++;
    }

    realloc(*tovar, (*length + 1)*sizeof(TOVAR))!=NULL; //kvoli warningu, lebo nepouzivam return value reallocu ale aj tak tu bool hodnotu nepouzijem

    for(int j=*length; j>i; j--) //posuvanie zaznamov o jedno hore
    {
        (*tovar)[j]=(*tovar)[j-1];
    }

    //skopirovanie temp premennych do zaznamu (pridanie prvkov)
    strcpy((*tovar)[i].nazov, nazov);
    strcpy((*tovar)[i].vyrobca, vyrobca);

    (*tovar)[i].pocet_kusov=pocet_kusov;
    (*tovar)[i].jednot_cena=jednot_cena;

    *length+=1;
}
