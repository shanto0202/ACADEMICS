#include <stdio.h>
int main()
{
    float a, b;
    printf("Enter two numbers:");
    char ope;
    scanf("%f %c %f", &a, &ope, &b);
    float result;
    if (ope == '+')
    {
        result = a + b;
    }
    else if (ope == '-')
    {
        result = a - b;
    }

    else if (ope == '*')
    {
        result = a * b;
    }
    else if (ope == '/')
    {
        if (b != 0)
        {
            result = a / b;
        }
        else
        {
            printf("Can't divided by zero");
        }
    }
    else
    {
        printf("Invalid operator");
    }

    printf("Result=%f",result);

    return 0;
}