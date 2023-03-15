/*
    MAREK CEDERLE, PROJEKT c.2 PRPR - Spajany zoznam struktur
    AIS ID: 121193
*/

/*
    Vsetko bolo otestovane a funguje podla zadania, bez errorov a warningov
    Pouzite IDE: VS Code v1.73.1
    Pouzity kompilator:
    gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
    Copyright (C) 2019 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //string compare, praca so stringami
#include <ctype.h> //isdigit

typedef struct zaznam {
    long long ID;
    char meno[31]; //o jedno viac kvoli null char
    char mer_mod[4]; //o jedno viac kvoli null char
    char mer_vel[3]; //o jedno viac kvoli null char
    double hodnota;
    char cas_mer[5]; //o jedno viac kvoli null char
    long long datum;
    struct zaznam *dalsi;
} ZAZNAM;

/*main functions*/
void n(FILE **f, ZAZNAM **start, int *record_count); //load
void v(ZAZNAM *start, int record_count); //print
void z(ZAZNAM **start, int *record_count); //zmazanie podla ID
void u(ZAZNAM **start, int *record_count); //sort pola vzostupne podla datumu a casu
void p(ZAZNAM **start, int *record_count); //pridanie zaznamu
void h(ZAZNAM *start); //print podla mer mod
void r(ZAZNAM *start, int record_count); //swapne dva zaznamy podla vstupu pozicii


/*help functions*/
void swap(ZAZNAM *one, ZAZNAM *two); //swapuje dva zaznamy medzi sebou


int main()
{
    char input;
    int record_count=0;
    ZAZNAM *zaznamy=NULL;
    FILE *f=NULL;
    
    while(1)
    {
        printf("\n"); //nech pekne oddeluje aby sa dalo zorientovat
        scanf("%c", &input);

        switch (input)
        {
            case 'n':
                n(&f, &zaznamy, &record_count);
                break;
            case 'v':
                v(zaznamy, record_count);
                break;
            case 'z':
                z(&zaznamy, &record_count);
                break;
            case 'u':
                u(&zaznamy, &record_count);
                break;
            case 'p':
                p(&zaznamy, &record_count);
                break;
            case 'h':
                h(zaznamy);
                break;
            case 'r':
                r(zaznamy, record_count);
                break;
            case 'k':
                if(zaznamy!=NULL)
                {
                    ZAZNAM *tmp1=zaznamy;
                    while(tmp1!=NULL)
                    {
                        zaznamy=zaznamy->dalsi;
                        free(tmp1);
                        tmp1=zaznamy;
                    }
                }

                return 0;
            default:
                ;
        }
    }

    return 0;
}

void n(FILE **f, ZAZNAM **start, int *record_count)
{
    if(*start!=NULL) //ak predtym existoval uvolni pamat
    {
        ZAZNAM *tmp1=*start;
        while(tmp1!=NULL)
        {
            *start=(*start)->dalsi;
            free(tmp1);
            tmp1=*start;
        }

        *record_count=0;
    }

    if((*f=fopen("dataloger_V2.txt", "r"))!=NULL) //ak sa podarilo otvorit
    {       
        //alokuje prvu poziciu
        *start=(ZAZNAM *)malloc(sizeof(ZAZNAM));
        ZAZNAM *tmp =*start;

        while(fscanf(*f, "%*s %lld %30[^\n\r] %s %s %lf %s %lld", &tmp->ID, tmp->meno, tmp->mer_mod, tmp->mer_vel, &tmp->hodnota, tmp->cas_mer, &tmp->datum)!=EOF) //*s znamena ze sa to preskoci, ten specialny format zoberie 30charov okrem danych vynimiek
        {
            tmp->dalsi=(ZAZNAM *)malloc(sizeof(ZAZNAM));
            tmp=tmp->dalsi;
            (*record_count)++;
        }

        tmp=NULL; //aby posledny ukazoval na koniec
        printf("Nacitalo sa %d zaznamov\n", *record_count);
    }
    else //vypise ak subor nie je mozne otvorit
    {
        printf("Zaznamy neboli nacitane!\n");
    }

    fclose(*f);
}

void v(ZAZNAM *start, int record_count)
{
    if(start==NULL) //ak neexistuje linked list
    {
        return;
    }

    ZAZNAM *tmp=start;
    int count=1;
    
    /*regulerny print*/

    while(tmp->dalsi!=NULL)
    {
        printf("%d:\nID cislo mer. osoby: %lld\nMeno osoby: %s\nMer. modul: %s\nTyp mer. veliciny: %s\nHodnota: %lf\nCas merania: %s\nDatum: %lld\n\n", count++, tmp->ID, tmp->meno, tmp->mer_mod, tmp->mer_vel, tmp->hodnota, tmp->cas_mer, tmp->datum);
        tmp=tmp->dalsi;
    }

    /*testovaci prehladny print*/
/*
    while(tmp->dalsi!=NULL)
    {
        printf("%2d: %lld  %30s  %s  %s  %lf\t%s  %lld\n", count++, tmp->ID, tmp->meno, tmp->mer_mod, tmp->mer_vel, tmp->hodnota, tmp->cas_mer, tmp->datum);
        tmp=tmp->dalsi;
    }
*/
}

void z(ZAZNAM **start, int *record_count)
{
    if(*start==NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    long long delete_ID;
    scanf("%lld", &delete_ID);

    ZAZNAM *tmp=*start;
    ZAZNAM *predch=NULL;
    while(tmp->dalsi!=NULL)
    {
        if(tmp->ID==delete_ID)
        {
            printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", delete_ID, tmp->mer_mod);

            if(predch==NULL) //ak je to prvy zaznam
            {
                *start=(*start)->dalsi; //posunie start na dalsi
                free(tmp); //uvolni ten prvy zaznam ktory sa maze
                tmp=*start; //nastavi novy zaciatok
            }
            else //ak je to niekde v strede
            {
                predch->dalsi=tmp->dalsi; //predch dalsi je vlastne aktualni a prehodi na neho šipku aktualneho dalsieho aby sme mohli aktualni uvolnit
                ZAZNAM *tmp2=tmp; //tento proces uvolnuje a nastavuje na dalsi
                free(tmp2);
                tmp=predch->dalsi;
            }

            (*record_count)--;
        }
        else
        {
            predch=tmp;
            tmp=tmp->dalsi;
        }
    }

    //vymaze ak zadany bol posledny zaznam
    if(tmp->ID==delete_ID)
    {
        printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", delete_ID, tmp->mer_mod);
        free(tmp->dalsi);
        tmp=NULL;
        free(tmp);
        predch->dalsi=NULL;
        (*record_count)--;
    }
}

void u(ZAZNAM **start, int *record_count)
{
    if(*start==NULL)
    {
        printf("Chyba\n");
        return;
    }

    ZAZNAM *tmp=*start;
    ZAZNAM *tmp2=NULL;

    while(tmp!=NULL)
    {
        tmp2=tmp->dalsi;
        while(tmp2!=NULL)
        {
            if(tmp2->dalsi==NULL)
            {
                break;
            }

            int compare=0;

            if(tmp->datum > tmp2->datum) //zoradujem primarne podla datumov
            {
                compare=1;
            }
            else if(tmp->datum==tmp2->datum && (strcmp(tmp->cas_mer, tmp2->cas_mer)>0)) //ak su datumy zhodne zoradujem podla casov
            {
                compare=1;
            }

            if(compare==1)
            {
                swap(tmp, tmp2);
            }

            tmp2=tmp2->dalsi;
        }

        tmp=tmp->dalsi;
    }

    printf("Spajany zoznam bol usporiadany.\n");
}

void p(ZAZNAM **start, int *record_count)
{
    if(*start==NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    int input;
    scanf("%d", &input);

    if(input<=0)
    {
        return;
    }

    ZAZNAM *tmp=*start;
    ZAZNAM *tmp2=NULL;

    if(input>*record_count) //ak je input mimo linked listu
    {
        while(tmp->dalsi!=NULL) //tento loop iba prejde na koniec zoznamu
        {
            tmp=tmp->dalsi;
        }
        tmp->dalsi=(ZAZNAM *)malloc(sizeof(ZAZNAM));
        tmp->dalsi->dalsi=NULL;

        (*record_count)++;
    }
    else if (input==1) //ak je to prvy zaznam
    {
        tmp=(ZAZNAM *)malloc(sizeof(ZAZNAM));
        tmp->dalsi=*start;
        *start=tmp;
 
        (*record_count)++;
    }
    else //ak je niekde v strede
    {
        for(int i=1; i<input-1; i++) //loopne to na poziciu kde chceme pridať -1 aby sme to vedeli posunúť
        {
            tmp=tmp->dalsi;
        }
        tmp2=tmp->dalsi;
        tmp->dalsi=(ZAZNAM *)malloc(sizeof(ZAZNAM));
        tmp=tmp->dalsi;
        tmp->dalsi=tmp2;

        (*record_count)++;
    }

    printf("Zadajte ID cislo mer. osoby: ");
    scanf("%lld", &tmp->ID);
    getchar(); //kvoli enteru, ten inak ten specialny format bral a skakalo to o jeden input nizsie

    printf("Zadajte meno osoby: ");
    scanf("%30[^\n]s", tmp->meno);

    printf("Zadajte mer. modul: ");
    scanf("%s", tmp->mer_mod);

    printf("Zadajte typ mer. veliciny: ");
    scanf("%s", tmp->mer_vel);

    printf("Zadajte hodnotu: ");
    scanf("%lf", &tmp->hodnota);

    printf("Zadajte cas merania: ");
    scanf("%s", tmp->cas_mer);

    printf("Zadajte datum: ");
    scanf("%lld", &tmp->datum);
}

void h(ZAZNAM *start)
{
    if(start==NULL) //overuje zaznami ci uz boli nacitane
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    /*input*/
    char input[4];
    scanf("%s", input);
    input[3]='\0';

    ZAZNAM *tmp=start;
    int count=1; //iba cisluje
    int zhoda=0; //ak sa vobec nejake zaznami nasli pre dany modul

    while(tmp->dalsi!=NULL)
    {
        if((strcmp(tmp->mer_mod, input))==0)
        {
            zhoda=1;

            /*regulerny print*/

            printf("%d:\nID cislo mer. osoby: %lld\nMeno osoby: %s\nMer. modul: %s\nTyp mer. veliciny: %s\nHodnota: %lf\nCas merania: %s\nDatum: %lld\n\n", count, tmp->ID, tmp->meno, tmp->mer_mod, tmp->mer_vel, tmp->hodnota, tmp->cas_mer, tmp->datum);

            /*test print*/
/*            
            printf("%2d: %lld  %30s  %s  %s  %lf\t%s  %lld\n", count, tmp->ID, tmp->meno, tmp->mer_mod, tmp->mer_vel, tmp->hodnota, tmp->cas_mer, tmp->datum);
*/
        }

        count++;
        tmp=tmp->dalsi;
    }

    if(zhoda==0)
    {
        printf("Pre meraci modul %s niesu zaznamy.\n", input);
    }
}

void r(ZAZNAM *start, int record_count)
{
    if(start==NULL) //overuje zaznami ci uz boli nacitane
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    /*input*/
    int c1,c2;
    scanf("%d %d", &c1, &c2);

    if(c1<=0 || c2<=0 || c1==c2 || c1>record_count || c2>record_count) //zistuje pripady kedy to nema zmysel
    {
        return;
    }

    ZAZNAM *tmp=start;
    ZAZNAM *tmp2=NULL; //ulozim si do temp premennych ak najdem zhodu
    ZAZNAM *tmp3=NULL;
    int count=1;

    while(tmp->dalsi!=NULL)
    {
        if(count==c1)
        {
            tmp2=tmp;
        }
        if(count==c2)
        {
            tmp3=tmp;
        }

        if(tmp2!=NULL && tmp3!=NULL)
        {
            break;
        }
        
        tmp=tmp->dalsi;
        count++;
    }
    
    swap(tmp2, tmp3);
}

void swap(ZAZNAM *one, ZAZNAM *two)
{
    /*vymeni samotne pointeri na zaznam*/
    ZAZNAM temp=*one;
    *one=*two;
    *two=temp;

    /*musi vymenit aj na co ukazuju dalsi */
    ZAZNAM *tempDalsi=one->dalsi;
    one->dalsi=two->dalsi;
    two->dalsi=tempDalsi;
}
