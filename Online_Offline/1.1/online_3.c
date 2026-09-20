#include <stdio.h>
#include <string.h>
int CountChar(char str[], char c)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
        {
            count++;
        }
    }
    return count;
}
int findChar(char ch, int n, char str[])
{
    int res = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            char temp[1001];
            int p = 0;
            for (int k = i; k <= j; k++)
            {
                temp[p++] = str[k];
            }
            temp[p] = '\0';
            int t = CountChar(temp, ch);
            if (t >= n)
            {
                res++;
            }
        }
    }
    return res;
}
int main()
{
    char ch;
    int n;
    char str[1001];
    scanf(" %c %d", &ch, &n);
    scanf("%s", str);
    int result = findChar(ch, n, str);
    printf("%d\n", result);
    return 0;
}
