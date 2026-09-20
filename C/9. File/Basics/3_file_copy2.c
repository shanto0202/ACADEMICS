#include <stdio.h>
int main()
{
    FILE *fp1, *fp2;
    char s[80], t[80], ch;
    scanf("%s", s);
    scanf("%s", t);
    // fgets(s,sizeof(s),stdin);
    // s[strcsp(s,"\n")]=='\0';
    // fgets(t,sizeof(t),stdin);
    // t[strcsp(t,"\n")]=='\0';
    fp1 = fopen(s, "r");
    fp2 = fopen(t, "w");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("ERROR");
        return 0;
    }
    while ((ch = fgetc(fp1)) != EOF)
    {
        fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}