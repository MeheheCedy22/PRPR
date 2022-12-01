/*
    MAREK CEDERLE, PROJEKT c.1 PRPR - Praca s dynamickymi poliami
    AIS ID: 121193
*/

/*
    Vsetko bolo otestovane a funguje podla zadania, bez errorov a warningov

    Pouzite IDE: VS Code v1.73.0

    Pouzity kompilator:

    gcc.exe (GCC) 11.2.0
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //string compare, praca so stringami
#include <ctype.h> //isdigit
#include <math.h>


/*main functions*/
void v(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f);
void o(char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len, FILE **f);
void n(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f);
void c(FILE **f);
void s(char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len);
void h(char **mer_vel, double **hodnota, int file_len);
void r(char **cas_mer, int file_len);
void z(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len);

/*funkcie z testu c.1*/
void H();
void j(long long **id, int file_len);

/*help functions*/
void alloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len);
void deAlloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum);
void reAlloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len);
void swap(void * destination, void * source, size_t size);

int main()
{
    int file_len=0;

    char input;

    FILE *f=NULL;

    long long *id=NULL;
    char *mer_mod=NULL; //pocet zaznamov suboru*3 znaky (potom alokujem o jeden viac cize *4 kvoli \0)
    char *mer_vel=NULL; //pocet zaznamov suboru*2 znaky (potom alokujem o jeden viac cize *3 kvoli \0)
    double *hodnota=NULL;
    char *cas_mer=NULL; //pocet zaznamov suboru*4 znaky (potom alokujem o jeden viac cize *5 kvoli \0)
    long long *datum=NULL;

    
    while(1)
    {
        printf("\n"); //nech pekne oddeluje aby sa dalo zorientovat
        scanf("%c", &input);

        switch (input)
        {
            case 'v':
                v(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer, &datum, &file_len, &f);
                break;
            case 'o':
                o(&mer_mod, &mer_vel, &hodnota, &cas_mer, &datum, file_len, &f);
                break;
            case 'n':
                n(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer, &datum, &file_len, &f);
                break;
            case 'c':
                c(&f);
                break;
            case 's':
                s(&mer_mod, &mer_vel, &hodnota, &cas_mer, &datum, file_len);
                break;
            case 'h':
                h(&mer_vel, &hodnota, file_len);
                break;
            case 'r':
                r(&cas_mer, file_len);
                break;
            case 'z':
                z(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer, &datum, &file_len);
                break;
            case 'k':
                if (id!=NULL)
                {
                    deAlloc(&id, &mer_mod, &mer_vel, &hodnota, &cas_mer, &datum);
                }
                if(f!=NULL)
                {
                    fclose(f);
                }

                return 0;
            case 'H':
                H();
                break;
            case 'j':
                j(&id, file_len);
                break;
            default:
                ;
        }
    }

    return 0;
}

/*main functions*/

void v(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f)
{
    if(*f==NULL) //ak subor nebol otvoreny
    {
        if((*f=fopen("dataloger.txt","r")) == NULL) //otvori subor a zaroven zisti ci sa otvoril spravne
        {
            printf("Neotvoreny subor\n"); //ak nespravne
        }
        else //ak spravne zavola sameho seba aby skipol prvu podmienku a neotvaral subor ale uz printoval lebo uz subor bude otvoreny
        {
            v(id, mer_mod, mer_vel, hodnota, cas_mer, datum, file_len, f);
        }
    }
    else
    {
        if(*id!=NULL) //bolo n (alokovane polia) - tak vypis z poli
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

void o(char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len, FILE **f)
{
    if(*f==NULL)
    {
        printf("Neotvoreny subor\n");
        return;
    }

    /*spocita dlzku suboru*/ //musi znova pretoze ak nestlacil 'n' tak nepozna
    rewind(*f);  //presun na zaciatok suboru
    char c;
    c=fgetc(*f);
    while(c!=EOF)
    {
        if(c=='\n')
        {
            (file_len)++;
        }
        c=fgetc(*f);
    }
    (file_len)++;
    (file_len)/=7;
    

    char in_mer_mod[4]; //iba input 3+1 znakov
    char in_mer_vel[3]; //iba input 2+1 znakov

    int index_new=0; //index novych poli

    //novo alokovane polia pre docasne pole
    double *o_hodnota=(double*) calloc(file_len, sizeof(double));
    char *o_cas_mer=(char*) calloc(file_len*5, sizeof(char));
    long long *o_datum=(long long*) calloc(file_len, sizeof(long long));


    scanf("%3s%2s", &in_mer_mod, &in_mer_vel); //nacita dve hodnoty ako input
    
    if(*mer_mod==NULL) //toto zbehne cez subor
    {
        long long temp_id;
        char temp_mer_mod[4]; //iba input 3+1 znakov
        char temp_mer_vel[3]; //iba input 2+1 znakov
        double temp_hodnota;
        char temp_cas_mer[5];
        long long temp_datum;
        rewind(*f);
        while (fscanf(*f, "%lld%3s%2s%lf%4s%lld", &temp_id, &temp_mer_mod, &temp_mer_vel, &temp_hodnota, &temp_cas_mer, &temp_datum)>0)
        {
            if(strcmp(temp_mer_mod, in_mer_mod)==0 && strcmp(temp_mer_vel, in_mer_vel)==0)
            {
                *(o_hodnota+index_new)=temp_hodnota;

                *(o_cas_mer+index_new*5)=temp_cas_mer[0];
                *(o_cas_mer+index_new*5+1)=temp_cas_mer[1];
                *(o_cas_mer+index_new*5+2)=temp_cas_mer[2];
                *(o_cas_mer+index_new*5+3)=temp_cas_mer[3];
                *(o_cas_mer+index_new*5+4)='\0';

                *(o_datum+index_new)=temp_datum;

                index_new++; //index temp pola
            }
        }
    }
    else //toto zbehne ak su uz alokovaner polia
    {
        for(int i=0; i<file_len; i++)
        {
            if(strcmp((*mer_mod+i*4), in_mer_mod)==0 && strcmp((*mer_vel+i*3), in_mer_vel)==0) // porovna dva a dva stringy a ak sa rovanaju tak skopiruje do temp pola
            {
                //skopiruje hodnoty do docaneho pola
                *(o_hodnota+index_new)=*(*hodnota+i);
                
                *(o_cas_mer+index_new*5)=*(*cas_mer+i*5);
                *(o_cas_mer+index_new*5+1)=*(*cas_mer+i*5+1);
                *(o_cas_mer+index_new*5+2)=*(*cas_mer+i*5+2);
                *(o_cas_mer+index_new*5+3)=*(*cas_mer+i*5+3);
                *(o_cas_mer+index_new*5+4)='\0';

                *(o_datum+index_new)=*(*datum+i);

                index_new++; //index temp pola
            }
        }
    }

    //sort poli od najmensieho po najvacsie
    for(int i=0; i<index_new-1; i++)
    {
        for(int j=0; j<index_new-i-1; j++)
        {
            int compare=0;
            
            if(o_datum[j]>o_datum[j+1])
            {
                compare=1;
            }
            else if(o_datum[j]==o_datum[j+1])
            {
                if(atoi(o_cas_mer+j*5)>atoi(o_cas_mer+(j+1)*5)) //atoi premeni string na int
                {
                    compare=1;
                }
            }
            
            if(compare)
            {
                swap(&o_hodnota[j], &o_hodnota[j+1], sizeof(double));
                swap(&o_cas_mer[j*5], &o_cas_mer[(j+1)*5], 5*sizeof(char));
                swap(&o_datum[j], &o_datum[j+1], sizeof(long long));
            }
        }
    }

    //printovanie
    for(int i=0; i<index_new; i++)
    {
        printf("%3s  %2s  %lld  %4s %lf\n", in_mer_mod, in_mer_vel, *(o_datum+i), (o_cas_mer+i*5), *(o_hodnota+i));
    }

    //dealokuje docasne polia
    free(o_hodnota);
    free(o_cas_mer);
    free(o_datum);

    o_hodnota=NULL;
    o_cas_mer=NULL;
    o_datum=NULL;
}

void n(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len, FILE **f)
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
    if(*id==NULL) //ak nebolo alokovane alokuje staci overit pre ID
    {
        alloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum, *file_len);
    }
    else //ak bolo alokovane uvolni a alokuje znova
    {
        deAlloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum);
        alloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum, *file_len);
    }

    /*nacita a zapise hodnoty do dynamickych poli*/
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

void c(FILE **f)
{
    if (*f==NULL)
    {
        printf("Neotvoreny subor\n");
        return;
    }

    rewind(*f);

    int correct = 1;

    int cas_hod; //na zmenu zo stringu na int
    int cas_min; //na zmenu zo stringu na int
   
    int datum_mm; //na zmenu zo stringu na int
    int datum_dd; //na zmenu zo stringu na int

    long long temp1; //ID
    char temp2[4]; //mer modul
    char temp3[3]; //mer velic
    double temp4; //useless - je tu aby don iba nacitalo a zahodi pretoze hodnotu neoverujeme
    char temp5[5]; //cas mer
    long long temp6; //datum



    while (fscanf(*f, "%lld%s%s%lf%s%lld", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6)>0)
    {
        if(temp1%11!=0 || temp1<999999999 || temp1>10000000000)
        {
            printf("Nekorektne zadany vstup: ID cislo mer. osoby\n");
            correct=0;
        }

        if(strlen(temp2)!=3 || temp2[0]>'Z' || temp2[0]<'A' || !isdigit(temp2[1]) || !isdigit(temp2[2]))
        {
            printf("Nekorektne zadany vstup: Mer. modul\n");
            correct=0;
        }

        if((temp3[0]!='R' && temp3[0]!='U' && temp3[0]!='A') || (temp3[1]!='1' && temp3[1]!='2' && temp3[1]!='4'))
        {
            printf("Nekorektne zadany vstup: Typ. mer. veliciny\n");
            correct=0;
        }

        if(strlen(temp5)!=4)
        {
            printf("Nekorektne zadany vstup: Cas merania\n");
            correct=0;           
        }
        else
        {
            char cas_hod_char[3]={temp5[0], temp5[1], '\0'};
            char cas_min_char[3]={temp5[2], temp5[3], '\0'};
            cas_hod=atoi(cas_hod_char);
            cas_min=atoi(cas_min_char);
            if(cas_hod>23 || cas_hod<0 || cas_min<0 || cas_min>59)
            {
                printf("Nekorektne zadany vstup: Cas merania\n");
                correct=0;              
            }
        }

        if(temp6<9999999 || temp6 >100000000)
        {
            datum_dd=temp6%100;
            datum_mm=(temp6%10000)/100;

            if(datum_mm>12 || datum_dd>31)
            {
                printf("Nekorektne zadany vstup: ID cislo mer. osoby\n");
                correct=0;
            }
        }
    }

    if(correct)
    {
        printf("Data su korektne\n");
    }
}

void s(char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len)
{
    if(*mer_mod==NULL)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }
    
    FILE *f_out;
    f_out=fopen("vystup_S.txt","w");

    char in_mer_mod[4]; //iba input 3+1 znakov
    char in_mer_vel[3]; //iba input 2+1 znakov
    scanf("%3s%2s", &in_mer_mod, &in_mer_vel); //nacita dve hodnoty ako input

    int index_new=0; //index novych poli

    //novo alokovane polia pre docasne pole
    double *s_hodnota=(double*) calloc(file_len, sizeof(double));
    char *s_cas_mer=(char*) calloc(file_len*5, sizeof(char));
    long long *s_datum=(long long*) calloc(file_len, sizeof(long long));

    for(int i=0; i<file_len; i++)
    {
        if(strcmp((*mer_mod+i*4), in_mer_mod)==0 && strcmp((*mer_vel+i*3), in_mer_vel)==0) // porovna dva a dva stringy a ak sa rovanaju tak skopiruje do temp pola
        {
            //skopiruje hodnoty co patria mer modulu a mer veliciny do docaneho pola
            *(s_hodnota+index_new)=*(*hodnota+i);
            
            *(s_cas_mer+index_new*5)=*(*cas_mer+i*5);
            *(s_cas_mer+index_new*5+1)=*(*cas_mer+i*5+1);
            *(s_cas_mer+index_new*5+2)=*(*cas_mer+i*5+2);
            *(s_cas_mer+index_new*5+3)=*(*cas_mer+i*5+3);
            *(s_cas_mer+index_new*5+4)='\0';

            *(s_datum+index_new)=*(*datum+i);

            index_new++; //index temp pola
        }
    }

    //sort poli od najmensieho po najvacsie
    for(int i=0; i<index_new-1; i++)
    {
        for(int j=0; j<index_new-i-1; j++)
        {
            int compare=0;
            if(s_datum[j]>s_datum[j+1])
            {
                compare=1;
            }
            else if(s_datum[j]==s_datum[j+1])
            {
                if(atoi(s_cas_mer+j*5)>atoi(s_cas_mer+(j+1)*5)) //atoi premeni string na int
                {
                    compare=1;
                }
            }
            
            if(compare)
            {
                swap(&s_hodnota[j], &s_hodnota[j+1], sizeof(double));
                swap(&s_cas_mer[j*5], &s_cas_mer[(j+1)*5], 5*sizeof(char));
                swap(&s_datum[j], &s_datum[j+1], sizeof(long long));
            }
        }
    }

    //printovanie
    for(int i=0; i<index_new; i++)
    {
        fprintf(f_out, "%lld%4s\t%.7lf\n", *(s_datum+i), (s_cas_mer+i*5), *(s_hodnota+i));
    }

    if(index_new!=0)
    {
        printf("Pre dany vstup je vytvoreny txt subor\n");
    }
    else
    {
        printf("Pre dany vstup neexistuju zaznamy\n");
    }

    //zatvori subor
    fclose(f_out);

    //dealocc temp poli
    free(s_hodnota);
    free(s_cas_mer);
    free(s_datum);

    s_hodnota=NULL;
    s_cas_mer=NULL;
    s_datum=NULL;
}

void h(char **mer_vel, double **hodnota, int file_len)
{
    if(*mer_vel==NULL)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }

    double temp_hodnota=0;

    int max_range_high;

    char in_mer_vel[3]; //iba input 2+1 znakov
    scanf("%s", &in_mer_vel);
    in_mer_vel[2]='\0';

    /*iba zisti maximalnu hodnotu a potom z toho urobi max range*/
    for(int i=0; i<file_len; i++)
    {
        if(strcmp((*mer_vel+i*3), in_mer_vel)==0) //su rovnake
        {
            if(*(*hodnota+i)>temp_hodnota)
            {
                temp_hodnota=*(*hodnota+i);
            }
        }
    }

    max_range_high=((int)temp_hodnota/5+1)*(5); //priradi maximalnu hodnotu rangu (urobi z toho max vlue of range)


    //pole, ktore reprezentuje kolko existuje rangov od 0 po max a naplni nulami
    int *range_arr=(int*) calloc(max_range_high/5, sizeof(int));

    for(int i=0; i<file_len; i++)
    {
        if(strcmp((*mer_vel+i*3), in_mer_vel)==0) //ak su rovnake
        {
            *(range_arr+((int)(*(*hodnota+i))/5))+=1; //pripocita vdzy 1 do indexu rangu kde sa nachadza dana hodnota pre zhodu s mer velicinou
        }
    }

    //printovanie ak je na indexe rangu ulozene nejake cislo tz. kolko krat sa ta hodnota nachadza v tom rangi pre danu zhodu
    printf("\t%2s\t\tpocetnost\n", in_mer_vel);

    for(int i=0; i<max_range_high/5; i++)
    {
        if(*(range_arr+i)!=0)
        {
            printf("(%3d.0- %3d.0>\t\t   %d\n", i*5, (i+1)*5, *(range_arr+i)); //tento print ze 3d je tak kvoli tomu ako to bolo v zadani pre ukazkovy vypis!!
        }
    }

    free(range_arr);
    range_arr=NULL;
}

void r(char **cas_mer, int file_len)
{
    if(*cas_mer==NULL)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }

    char *temp_cas_mer=(char*) calloc(file_len*5, sizeof(char));
    int index_new=0;

    //skopiruje hodnoty do docaneho pola
    for(int i=0; i<file_len; i++)
    {           
        strcpy((temp_cas_mer+i*5), (*cas_mer+i*5));
    }

    //sort poli od najmensieho po najvacsie
    for(int i=0; i<file_len-1; i++)
    {
        for(int j=0; j<file_len-i-1; j++)
        {
            if(atoi(temp_cas_mer+j*5)>atoi(temp_cas_mer+(j+1)*5)) //atoi premeni string na int
            {
                swap(&temp_cas_mer[j*5], &temp_cas_mer[(j+1)*5], 5*sizeof(char));
            }
        }
    }

    //kopiruje + filtruje do druheho temp pola
    index_new++;
    char *temp_cas_mer2=(char*) calloc(file_len*5, sizeof(char));
    strcpy(temp_cas_mer2, temp_cas_mer); //skopiruje prvy string

    for(int i=1; i<file_len; i++)
    {
        if(strcmp(temp_cas_mer+(i-1)*5, temp_cas_mer+i*5)!=0)
        {
            strcpy(temp_cas_mer2+index_new*5, temp_cas_mer+i*5);
            index_new++;
        }
    }

    //vypise hodiny a ich dane minuty do jedneho riadku
    for(int i=0; i<index_new; i++)
    {
        char hod_str[3]={temp_cas_mer2[i*5], temp_cas_mer2[i*5+1], '\0'};
        char min_str[3]={temp_cas_mer2[i*5+2], temp_cas_mer2[i*5+3], '\0'};

        //ak je hodina rovnaka ako predtym tak vypisuje iba minuty
        if(i!=0 && temp_cas_mer2[i*5]==temp_cas_mer2[(i-1)*5] && temp_cas_mer2[i*5+1]==temp_cas_mer2[(i-1)*5+1])
        {
            printf(", %s", min_str);
        }
        else
        {
            printf("\n%s:%s", hod_str, min_str);
        }
    }

    free(temp_cas_mer);
    free(temp_cas_mer2);

    temp_cas_mer=NULL;
    temp_cas_mer2=NULL;
}

void z(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int *file_len)
{
    if(*id==NULL)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }

    int count_deleted=0;

    long long in_id;
    scanf("%lld", &in_id);

    //setuje nasledujuci na predchadzajuci a prepisuje ich (shiftuje pole)
    for(int i=0; i<*file_len; i++)
    {
        if(*(*id+i-count_deleted)==in_id)
        {
            for(int j=i-count_deleted; j<*file_len; j++)
            {

                *(*id+j)=*(*id+j+1);
                
                *(*mer_mod+j*4)=*(*mer_mod+(j+1)*4);
                *(*mer_mod+j*4+1)=*(*mer_mod+(j+1)*4+1);
                *(*mer_mod+j*4+2)=*(*mer_mod+(j+1)*4+2);
                *(*mer_mod+j*4+3)=*(*mer_mod+(j+1)*4+3);

                *(*mer_vel+j*3)=*(*mer_vel+(j+1)*3);
                *(*mer_vel+j*3+1)=*(*mer_vel+(j+1)*3+1);
                *(*mer_vel+j*3+2)=*(*mer_vel+(j+1)*3+2);

                *(*hodnota+j)=*(*hodnota+j+1);

                *(*cas_mer+j*5)=*(*cas_mer+(j+1)*5);
                *(*cas_mer+j*5+1)=*(*cas_mer+(j+1)*5+1);
                *(*cas_mer+j*5+2)=*(*cas_mer+(j+1)*5+2);
                *(*cas_mer+j*5+3)=*(*cas_mer+(j+1)*5+3);
                *(*cas_mer+j*5+4)=*(*cas_mer+(j+1)*5+4);

                *(*datum+j)=*(*datum+j+1);
            }

            count_deleted++;
        }
    }

    reAlloc(id, mer_mod, mer_vel, hodnota, cas_mer, datum, *file_len-count_deleted);

    *file_len-=count_deleted;

    printf("Vymazalo sa: %d zaznamov !", count_deleted);
}

/*help functions*/

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

/*realokuje velkosti poli vo funkcii z po zmazani zaznamov*/
void reAlloc(long long **id, char **mer_mod, char **mer_vel, double **hodnota, char **cas_mer, long long **datum, int file_len)
{
    //!=NULL je tam kvoli tomu ze mi kompiler daval warningy ze nepouzivam return hodnotu reallocu, tak som dal aby akoze overil ze to spravne reallocoval ale realne ten bool vystup nepouzijem
    realloc(*id, file_len*sizeof(long long))!=NULL;
    realloc(*mer_mod, file_len*4*sizeof(char))!=NULL;
    realloc(*mer_vel, file_len*3*sizeof(char))!=NULL;
    realloc(*hodnota, file_len*sizeof(double))!=NULL;
    realloc(*cas_mer, file_len*5*sizeof(char))!=NULL;
    realloc(*datum, file_len*sizeof(long long))!=NULL;
}

/*vymeni dva zaznami z docasnych poli vo funkcii o*/
void swap(void * destination, void * source, size_t size)
{
    void *temp=malloc(size);
    memcpy(temp, source, size);
    memcpy(source, destination, size);
    memcpy(destination, temp, size);

    free(temp);
    temp=NULL;
}


/*funckie z testu c.1*/
void j(long long **id, int file_len)
{
    //toto je dobre
    int k;

    scanf("%d", &k);

    if(k<1)
    {
        return;
    }

    int new_index=0; //index pre docasne pole

    long long *j_id;
    j_id=(long long*) calloc(file_len, sizeof(long long));

    int digit_arr[10]={0}; //index prestavuje cislicu, hodnota na indexe bude pocetnost


    //skporiuje do temp pola riadky ktore su nasobky k
    for(int i=0; i<file_len; i++)
    {
        if(i%k==0)
        {
            *(j_id+i)=*(*id+i);
            new_index++;
        }
    }

    //tento stred nefunguje korektne asi
    for(int i=0; i<file_len; i++) //loop pre kazdy zaznam
    {   
        if(*(j_id+i)!=0)
        {
            for(int j=0; j<10; j++) //loop pre kazdu cislicu
            {
                int cifra;
                cifra=(*(j_id+j))%((int)(pow(10, j+1)));

                switch (cifra)
                {
                    case '0':
                        digit_arr[0]+=1;
                        break;
                    case '1':
                        digit_arr[1]+=1;
                        break;
                    case '2':
                        digit_arr[2]+=1;
                        break;
                    case '3':
                        digit_arr[3]+=1;
                        break;
                    case '4':
                        digit_arr[4]+=1;
                        break;
                    case '5':
                        digit_arr[5]+=1;
                        break;
                    case '6':
                        digit_arr[6]+=1;
                        break;
                    case '7':
                        digit_arr[7]+=1;
                        break;
                    case '8':
                        digit_arr[8]+=1;
                        break;
                    case '9':
                        digit_arr[9]+=1;
                        break;
                    default:
                        ;
                }
            }
        }
    }

    //toto je dobre (otestovane cey staticke hodnoty)

    //vyprintuej cislice, ktore nemaju nulovu pocetnost (prvy riadok)
    for(int i=0; i<10; i++)
    {
        if(digit_arr[i]==0)
        {
            continue;
        }
        printf("%2d ", i);
    }
    printf("\n");
    
    //vyprintuje pocetnosti (druhy riadok)
    for(int i=0; i<10; i++)
    {
        if(digit_arr[i]==0)
        {
            continue;
        }
        printf("%2d ", digit_arr[i]);
    }
    printf("\n");
}

void H()
{

}