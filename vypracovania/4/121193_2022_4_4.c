#include <stdio.h>

int sum(int x);

int main()
{
    int N;
    scanf("%d",&N);

    printf("%d",sum(N-1)); //n-1 pretoze mensich celych cisel ako n

    return 0;
}

int sum(int x)
{
    if(x>0)
    {
        if(x%2!=0)
        {
            return x+sum(x-1);
        }
        return sum(x-1);
    }


    return 0;
}