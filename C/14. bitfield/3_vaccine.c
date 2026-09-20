#include <stdio.h>
/*You want to store the vaccination of diphtheria, typhoid, cholera, polio, tetanus,
measles applied to a child. Which data type will beoptimal for storing this information?*/
struct VaccinationStatus
{
    unsigned int hasDiphtheria : 1;
    unsigned int hasTyphoid : 1;
    unsigned int hasCholera : 1;
    unsigned int hasPolio : 1;
    unsigned int hasTetanus : 1;
    unsigned int hasMeasles : 1;
};
int main()
{
    struct VaccinationStatus child1_vaccines;
    // Initialize all to 0 (not vaccinated)
    child1_vaccines.hasDiphtheria = 0;
    child1_vaccines.hasTyphoid = 0;
    child1_vaccines.hasCholera = 0;
    child1_vaccines.hasPolio = 0;
    child1_vaccines.hasTetanus = 0;
    child1_vaccines.hasMeasles = 0;
    // Update the status for vaccines that have been applied.
    child1_vaccines.hasDiphtheria = 1; // 1 means 'yes'
    child1_vaccines.hasPolio = 1;
    child1_vaccines.hasMeasles = 1;

    // Check the status of a specific vaccine.
    printf("Vaccination Status for Child 1:\n");
    if (child1_vaccines.hasPolio == 1)
    {
        printf("- Polio: Yes\n");
    }
    else
    {
        printf("- Polio: No\n");
    }

    if (child1_vaccines.hasTyphoid == 1)
    {
        printf("- Typhoid: Yes\n");
    }
    else
    {
        printf("- Typhoid: No\n");
    }
    // Prove the memory efficiency. This will print '1'.
    printf("\nTotal memory used: %lu byte(s)\n", sizeof(struct VaccinationStatus)); // 4 byte
    return 0;
}