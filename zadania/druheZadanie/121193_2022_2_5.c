#include <stdio.h>

int main()
{
    char c,ch;
    scanf("%c %c", &c, &ch);
    printf("\n%c %c\n", ch + 'a'-'A', c + 'a'-'A');

    return 0;
}