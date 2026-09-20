#include <stdio.h>
#include <string.h>
int No_Vowel_Number(char str[])
{
    char str_1[1001], str_2[1001];
    int c = 0, temp = 0, sub_string_len = 0;
    for (int i = 0; i <= strlen(str); i++)
    {
        if (
            str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' ||
            str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' ||
            str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9' || str[i]=='\n')
        {
            c++;
            if (i == 0)
            {
                temp = 0;
            }
            int k = 0;
            for (int j = i - 1; j >= temp; j--)
            {
                str_1[k] = str[j];
                k++;
            }
            if (k >= sub_string_len)
            {
                sub_string_len = k;
                str_1[k] = '\0';
                strcpy(str_2, str_1);
            }
            temp = i + 1;
        }
    }
    if (c == 0)
    {
        printf("1");
        return 0;
    }
    else if (strlen(str_2) == 0)
    {
        printf("No Substring\n");
        return 0;
    }
    else
    {
        int len = strlen(str_2);
        for (int i = 0; i < len / 2; i++)
        {
            char temp = str_2[i];
            str_2[i] = str_2[len - i - 1];
            str_2[len - i - 1] = temp;
        }
        fputs(str_2, stdout);
        return 0;
    }
}
int main()
{
    char str[1001];
    fgets(str, sizeof(str), stdin);
    No_Vowel_Number(str);
    return 0;
}