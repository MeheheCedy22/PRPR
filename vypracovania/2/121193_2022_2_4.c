#include <stdio.h>

int main()
{
    char c,ch;
    scanf("%c %c", &c, &ch);
    printf("\n%c %d\n%c %d\n", c + 'A'-'a', c + 'A'-'a', ch + 'A'-'a', ch + 'A'-'a');

    return 0;
}