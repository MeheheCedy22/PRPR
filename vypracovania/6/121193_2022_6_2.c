#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    char *arr;
    arr = (char *) malloc(n * sizeof(char));

    for(int i=0; i<=n; i++)
    {
        scanf("%c", &arr[i]);
    }

    for(int i=n; i>=0; i--)
    {
        printf("%c", arr[i]);
    }

    free(arr);

    return 0;
}