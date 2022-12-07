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
    struct tovar *next;

} TOVAR;

void vypis(TOVAR *start);
void add(TOVAR **start);
void rm(TOVAR **start);

int main()
{
    int n=1;
    char input;

    TOVAR *start=NULL;

    printf("\nk - ukonci program, v - vypis, p - pridanie do zoznamu, z -vymazanie zo zoznamu\n");

    while(1)
    {
        printf("\n");
        input=getchar();

        switch(input)
        {
            case 'z':
                rm(&start);
                break;
            case 'p':
                add(&start);
                break;
            case 'v':
                vypis(start);
                break;
            case 'k':
                if(start!=NULL)
                {
                    TOVAR *pom=start;
                    while(pom!=NULL)
                    {
                        start=start->next;
                        free(pom);
                        pom=start;
                    }
                }
                
                return 0;
            case '\n':
                break;
            default:
                printf("Zadal si zly vstup!\n");
                break;
        }
    }

    return 0;
}

void vypis(TOVAR *start)
{
    int i=1;

    printf("\nvypis\n\n");
    while(start!=NULL)
    {
        printf("%d:\n", i++);
        printf("Nazov tovaru: %s\n", start->nazov);
        printf("Nazov vyrobcu: %s\n", start->vyrobca);
        printf("Pocet kusov: %d\n", start->pocet_kusov);
        printf("Jednotkova cena: %d\n", start->jednot_cena);
        printf("\n");
        start=start->next;
    }
}

void add(TOVAR **start)
{
    TOVAR *current=*start;
    TOVAR *new=(TOVAR*)malloc(sizeof(TOVAR));

    printf("Zadajte tovar v nasledujucom tvare: \n");
    printf("Nazov vyrobca pocet_kusov jednotkova_cena\n");

    scanf("%s%s%d%d", new->nazov,  new->vyrobca, &new->pocet_kusov, &new->jednot_cena);

    if(current==NULL || strcmp(new->nazov, current->nazov)<0)
    {
        new->next=current;
        current=new;
    }
    else
    {
        
        while(current->next!=NULL && strcmp(new->nazov, current->next->nazov)>0)
        {
            current=current->next;
        }
        new->next=current->next;
        current->next=new;
    }
    
    *start=current;
}

void rm(TOVAR **start)
{
    char nazov[name_len];

    printf("Zadajte nazov tovaru, ktory chcete vymazat: \n");
    scanf("%s", nazov);

    TOVAR *current=*start;
    TOVAR *previous=NULL;

    while(current!=NULL)
    {
        if(strcmp(nazov, current->nazov)==0)
        {
            if(previous==NULL)
            {
                *start=current->next;
            }
            else
            {
                previous->next=current->next;
            }
            free(current);
            return;
        }
        previous=current;
        current=current->next;
    }
}