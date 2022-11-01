#include <stdio.h>
#include <stdlib.h>
#include <string.h> //string compare
#include <ctype.h> //isdigit func & so on


/*main functions*/
/*v*/void fileOpened(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f);
/*n*/void initArr(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f);

/*help functions*/
void alloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len);
void deAlloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum);
void reAlloc();


int main()
{
    int file_len=0;

    char input;

    FILE *f=NULL;

    long long *id=NULL;
    char *mer_mod=NULL; //3 znaky
    char *mer_vel=NULL; //2 znaky
    double *hodnota=NULL;
    char *cas_mer=NULL; //4 znaky
    long long *datum=NULL;

    
    while(1)
    {
        printf("\n");
        scanf("%c", &input);

        switch (input)
        {
            case 'v':
                fileOpened(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer,&datum, &file_len, &f);
                break;
            case 'o':

                break;
            case 'n':
                initArr(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer,&datum, &file_len, &f);
                break;
            case 'c':

                break;
            case 's':

                break;
            case 'h':

                break;
            case 'r':

                break;
            case 'z':

                break;
            case 'k':
                deAlloc(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer,&datum);
                fclose(f);
                return 0;

            default:
                ;
        }

    }

    return 0;
}

/*v*/
void fileOpened(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f)
{

    if(*f==NULL) //ak subor nebol otvoreny
    {
        if((*f=fopen("dataloger.txt","r")) == NULL) //otvori subor a zaroven zisti ci sa otvoril spravne
        {
            printf("Neotvoreny subor\n"); //ak nespravne
        }
        else //ak spravne zavola sameho seba aby skipol prvu podmienku a neotvaral subor ale uz printoval
        {
            fileOpened(id, mer_mod, mer_vel, hodnota, cas_mer, datum, file_len, f);
        }
        
    }
    else
    {
        if(*id!=NULL) //bolo n - tak vypis z poli
        {
            for(int i=0; i<*file_len; i++)
            {
                printf("ID cislo mer. osoby: %lld\nMer. modul: %s\nTyp mer. veliciny: %s\nHodnota: %lf\nCas merania: %s\nDatum: %lld\n\n", *(*id+i), (*mer_mod+i*4), (*mer_vel+i*3), *(*hodnota+i), (*cas_mer+i*5), *(*datum+i));
            }
        }
        else //nebolo n - vypis zo suboru
        {
            rewind(*f);
            long long temp1;
            char temp2[4];
            char temp3[3];
            double temp4;
            char temp5[5];
            long long temp6;
            while (fscanf(*f, "%lld%3s%2s%lf%4s%lld", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6)>0)
            {
                printf("ID cislo mer. osoby: %lld\nMer. modul: %3s\nTyp mer. veliciny: %2s\nHodnota: %lf\nCas merania: %4s\nDatum: %lld\n\n", temp1, temp2, temp3, temp4, temp5, temp6);
            }
        }
    }
}

/*n*/
void initArr(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f)
{
    if(*f==NULL) //ak nebol otvoreny (tz nebolo este v)
    {
        printf("Neotvoreny subor\n");
        return;
    }

    /*spocita dlzku suboru*/
    rewind(*f);  //presun na zaciatok suboru
    char c;
    c=fgetc(*f);
    while(c!=EOF)
    {
        if(c=='\n')
        {
            (*file_len)++;
        }
        c=fgetc(*f);
    }
    (*file_len)++;
    (*file_len)/=7;

    /*dynamicky vytvori polia*/
    if(*id!=NULL) //ak nebolo alokovane alokuje
    {
        alloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum, *file_len);
    }
    else //ak bolo alokovane uvolni a alokuje znova
    {
        deAlloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum);
        alloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum, *file_len);
    }
    /*nacita a zapise hodnoty do arrayov*/
    rewind(*f);
    long long temp1;
    char temp2[4]; //3+1 znak kvoli \0
    char temp3[3]; //2+1 znak kvoli \0
    double temp4;
    char temp5[5]; //4+1 znak kvoli \0
    long long temp6;
    for(int i=0; i<*file_len; i++)
    {
        fscanf(*f, "%lld%3s%2s%lf%4s%lld", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6);

        *(*id+i)=temp1;

        *(*mer_mod+i*4)=temp2[0];
        *(*mer_mod+i*4+1)=temp2[1];
        *(*mer_mod+i*4+2)=temp2[2];
        *(*mer_mod+i*4+3)='\0';

        *(*mer_vel+i*3)=temp3[0];
        *(*mer_vel+i*3+1)=temp3[1];
        *(*mer_vel+i*3+2)='\0';

        *(*hodnota+i)=temp4;

        *(*cas_mer+i*5)=temp5[0];
        *(*cas_mer+i*5+1)=temp5[1]; 
        *(*cas_mer+i*5+2)=temp5[2];
        *(*cas_mer+i*5+3)=temp5[3];
        *(*cas_mer+i*5+4)='\0';

        *(*datum+i)=temp6;
    }
}

/*alokuje vsetky polia a calloc ich automaticky nastavi na 0*/
void alloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len)
{
    *id=(long long*) calloc(file_len, sizeof(long long));
    *mer_mod=(char*) calloc(file_len*4, sizeof(char));
    *mer_vel=(char*) calloc(file_len*3, sizeof(char));
    *hodnota=(double*) calloc(file_len, sizeof(double));
    *cas_mer=(char*) calloc(file_len*5, sizeof(char));
    *datum=(long long*) calloc(file_len, sizeof(long long));
}

/*uvolni vsetky polia a nastavy zbytok na 0 kvoli security*/
void deAlloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum)
{
    free(*id);
    free(*mer_mod);
    free(*mer_vel);
    free(*hodnota);
    free(*cas_mer);
    free(*datum);

    *id=NULL;
    *mer_mod=NULL;
    *mer_vel=NULL;
    *hodnota=NULL;
    *cas_mer=NULL;
    *datum=NULL;
}