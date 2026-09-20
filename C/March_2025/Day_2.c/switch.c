#include <stdio.h>
int main()
{
    int a, b, result;
    char g;
    printf("Enter two numbers:");
    scanf("%d %c %d", &a, &g, &b);

    switch (g)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        // if (b == 0)
        // {
        //     printf("Not Valid");
        // }
        // else
        // {
        //     result = a / b;
        // }
        switch (b)
        {
        case 0:
            printf("Not Valid");
            break;

        default:
            result = a / b;
            break;
        }
        break;
    default:
        printf("Not Valid");
        break;
    }
    printf("%d", result);
    return 0;
}