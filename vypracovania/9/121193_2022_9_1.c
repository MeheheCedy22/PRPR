#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length 100
#define name_len 31

typedef struct clovek
{
    char meno[name_len];
    char temp[name_len]; //dlzka mena je max 30 znakov
} CLOVEK;

int main()
{
    CLOVEK clovek[length]={0};
    int pocetnost[length]={0};
    int new_index=0;

    printf("\nZadavaj mena po riadkoch, ak uz nechces zadat meno tak odriadkuj\n\n");

    for(int i=0; i<length; i++)
    {
        fgets(clovek[i].meno, name_len, stdin); //nacita string danej dlzky cez standartny vstup, vieme pouzit tuto funckiu lebo c pracuje aj so vstupom z klavesnice ako so suborom

        //dam prec novy riadok
        clovek[i].meno[strcspn(clovek[i].meno, "\n")] = 0;
        // Ak je meno (ten string) prazdny tak breaknem
        if(strcmp(clovek[i].meno, "")==0)
        {
            break;
        }

        //pre prve meno
        if(new_index==0) 
        {
            strcpy(clovek[new_index].temp, clovek[i].meno); //skopirujem si prve meno do dalsieho pola stringov
            pocetnost[new_index]=1;
        } 
        else //pre ostatne mena
        {
            int found=0;
            for(int j=0; j<new_index; j++) //iteruje po pocet skopirovanych mien a overuje ci uz take ma v jeho zozname
            {
                if(strcmp(clovek[j].temp, clovek[i].meno)==0) //pyta sa ci meno ktore nacital je v zozname
                {
                    pocetnost[j]++;
                    found=1;
                    break;
                }
            }
            if(found==0) //ak nenajde tak ho prida do zoznamu
            {
                strcpy(clovek[new_index].temp, clovek[i].meno);
                pocetnost[new_index]=1;
            }
        }
        
        new_index++;
    }

    //zisti ktore cislo v arrayi pocetnost je najvacsie
    int docasny_strop=pocetnost[0], index_max_pocetnosti=0;
    for (int i=0; i<new_index; i++)
    {
        if (pocetnost[i]>docasny_strop)
        {
            docasny_strop=pocetnost[i];
            index_max_pocetnosti=i;
        }
    }
    
    printf("Meno, ktore sa najviac vyskytuje je: %s\n", clovek[index_max_pocetnosti].temp);

    return 0;
}
