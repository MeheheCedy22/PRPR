#include <stdio.h>

int main()
{
    char array[15];

    for (int i=0;i<=14;i++)
    {
        scanf("%c", &array[i]);
        getchar(); // aby ignorovalo medzeri ako znaky, tz zobere jeden char a "zahodí ho" 
    }

    for (int j=14;j>=0;j--)
    {
        printf("%c",array[j]);
    }

    return 0;
}