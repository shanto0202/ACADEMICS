#include <stdio.h>
int main()
{
    int n = 4;
    // for(int i=4;i>0;i--){
    //     for(int j=0;j<i;j++){
    //         printf("* ");
    //     }
    //     printf("\n");
    // }

    // int n = 5;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = (n - i); j > 0; j--)
    //     {
    //         printf("* ");
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}