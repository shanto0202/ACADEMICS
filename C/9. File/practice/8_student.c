#include <stdio.h>
int main()
{
    FILE *fp;
    char name[50];
    int m1, m2, m3, m4, m5;
    fp = fopen("myfile.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    printf("Enter data for 10 students (Name and 5 subject marks):\n");
    for (int i = 0; i < 10; i++)
    {
        printf("Student %d Name: ", i + 1);
        scanf("%s", name);
        printf("Enter marks in 5 subjects: ");
        scanf("%d %d %d %d %d", &m1, &m2, &m3, &m4, &m5);
        fprintf(fp, "%s %d %d %d %d %d\n", name, m1, m2, m3, m4, m5);
    }
    fclose(fp);
    // Read data back and find highest/lowest
    fp = fopen("students.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    char top_name[50], low_name[50], temp_name[50];
    int total, max_total = -1, min_total = 9999;
    while (fscanf(fp, "%s %d %d %d %d %d", temp_name, &m1, &m2, &m3, &m4, &m5) == 6)
    {
        total = m1 + m2 + m3 + m4 + m5;
        if (total > max_total)
        {
            max_total = total;
            strcpy(top_name, temp_name);
        }
        if (total < min_total)
        {
            min_total = total;
            strcpy(low_name, temp_name);
        }
    }
    fclose(fp);
    printf("\nStudent with Highest Marks:\nName: %s, Total: %d\n", top_name, max_total);
    printf("Student with Lowest Marks:\nName: %s, Total: %d\n", low_name, min_total);
    return 0;
}