#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *decompressString(const char *encoded)
{
    // Calculate the length of the output string
    int output_len = 0;
    const char *p = encoded;
    while (*p != '\0')
    {
        char c = *p++;
        if (isalpha(c))
        {
            int num = 0;
            while (isdigit(*p))
            {
                num = num * 10 + (*p - '0');
                p++;
            }
            if (num > 0)
            {
                output_len += num;
            }
        }
    }

    // Allocate memory for the output string (+1 for null terminator)
    char *output = (char *)malloc(output_len + 1);
    if (output == NULL)
    {
        return NULL;
    }

    // Decompress the string
    char *out_ptr = output;
    p = encoded;
    while (*p != '\0')
    {
        char c = *p++;
        if (isalpha(c))
        {
            int num = 0;
            while (isdigit(*p))
            {
                num = num * 10 + (*p - '0');
                p++;
            }
            for (int i = 0; i < num; i++)
            {
                *out_ptr++ = c;
            }
        }
    }
    *out_ptr = '\0';

    return output;
}

int main()
{
    char encoded[100];
    scanf("%s", encoded);

    char *output = decompressString(encoded);
    if (output != NULL)
    {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}