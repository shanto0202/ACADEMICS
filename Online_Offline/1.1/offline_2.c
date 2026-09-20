#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 100000
#define MAX_BINS 1000
#define MAX_STARS 50
#define PI 3.14159265358979323846
// Given Functions
double generate_normal(double mu, double sigma)
{
    double U1 = (double)rand() / (double)RAND_MAX;
    double U2 = (double)rand() / (double)RAND_MAX;
    double X1 = sqrt(-2 * log(U1)) * cos(2 * PI * U2);
    return mu + sigma * X1;
}
void populate_array_gaussian(double *array, int size, double mu, double sigma, unsigned int seed)
{
    srand(seed);
    for (int i = 0; i < size; i++)
    {
        array[i] = generate_normal(mu, sigma);
    }
}
void populate_array_uniform(double *array, int size, double min, double max, unsigned int seed)
{
    srand(seed);
    for (int i = 0; i < size; i++)
    {
        array[i] = min + (double)rand() / ((double)RAND_MAX / (max - min));
    }
}

double arr[MAX_SIZE];
int size = 0;
int initialized = 0;
int count[MAX_BINS];
// Help message
void Help()
{
    printf("Commands:\n");
    printf("  set     - Set array size, seed, and distribution (uniform or gaussian)\n");
    printf("  min     - Print minimum value\n");
    printf("  max     - Print maximum value\n");
    printf("  mean    - Print mean value\n");
    printf("  stddev  - Print standard deviation\n");
    printf("  hist    - Plot histogram\n");
    printf("  summary - Print min, max, mean, stddev\n");
    printf("  help    - Show this help message\n");
    printf("  median  - Print median value\n");
    printf("  exit    - Exit the program\n");
}

// Set function
void Set()
{
    printf("Enter number of elements (<= %d): ", MAX_SIZE);
    scanf("%d", &size);
    if (size <= 0 || size > MAX_SIZE)
    {
        printf("Invalid size.\n");
        return;
    }
    unsigned int seed;
    printf("Enter seed: ");
    scanf("%u", &seed);
    char distribution[10];
    printf("Distribution? (uniform/gaussian): ");
    scanf("%s", distribution);
    if (strcmp(distribution, "uniform") == 0)
    {
        double min_val, max_val;
        printf("Enter min and max: ");
        scanf("%lf %lf", &min_val, &max_val);
        if (min_val >= max_val)
        {
            printf("Invalid min and max values.\n");
            return;
        }
        populate_array_uniform(arr, size, min_val, max_val, seed);
        initialized = 1;
        printf("Array initialized with uniform distribution.\n");
    }
    else if (strcmp(distribution, "gaussian") == 0)
    {
        double mean, stddev;
        printf("Enter mean and stddev: ");
        scanf("%lf %lf", &mean, &stddev);
        if (stddev <= 0)
        {
            printf("Standard deviation must be positive.\n");
            return;
        }
        populate_array_gaussian(arr, size, mean, stddev, seed);
        initialized = 1;
        printf("Array initialized with gaussian distribution.\n");
    }
    else
    {
        printf("Invalid distribution.\n");
    }
}

// functions to be used in the main function
double Minimum()
{
    double min = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < min)
        {
            min = arr[i];
        }
    return min;
}
double Maximum()
{
    double max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
double Mean()
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + arr[i];
    }
    return sum / size;
}
double Standard_deviation(double mean)
{
    double sum1 = 0;
    for (int i = 0; i < size; i++)
    {
        sum1 = sum1 + (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sum1 / size);
}

// Histogram function
void histogram()
{
    if (initialized == 0)
    {
        printf("Array not initialized. Use 'set' command first.\n");
        return;
    }
    int bins;
    printf("Enter number of bins: ");
    scanf("%d", &bins);
    if (bins <= 0 || bins > MAX_BINS)
    {
        printf("Invalid number of bins. Must be between 1 and 1000.\n");
        return;
    }
    double min = Minimum();
    double max = Maximum();
    double bin_width = (max - min) / bins;
    for (int i = 0; i < bins; i++)
    {
        count[i] = 0;
    }
    int max_count = 0;
    for (int i = 0; i < size; i++)
    {
        int idx = (int)((arr[i] - min) / bin_width);
        if (idx == bins)
        {
            idx = bins - 1;
        }
        count[idx]++;
        if (count[idx] > max_count)
        {
            max_count = count[idx];
        }
    }
    int max_stars = 50;
    for (int i = 0; i < bins; i++)
    {
        double start = min + i * bin_width;
        double end = start + bin_width;
        printf("[%6.2f - %6.2f]: ", start, end);
        int stars;
        if (max_count > 0)
        {
            stars = (count[i] * max_stars) / max_count;
        }
        else
        {
            stars = 0;
        }
        for (int j = 0; j < stars; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

// bonus for median
int compare(const void *a, const void *b)
{
    double x = *(const double *)a;
    double y = *(const double *)b;
    if (x < y)
    {
        return -1;
    }
    if (x > y)
    {
        return 1;
    }
    return 0;
}
double median()
{
    double arr_1[MAX_SIZE], t;
    for (int i = 0; i < size; i++)
    {
        arr_1[i] = arr[i];
    }
    qsort(arr_1, size, sizeof(double), compare);
    if (size % 2 == 1)
    {
        t = arr_1[size / 2];
        return t;
    }
    else
    {
        t = (arr_1[size / 2 - 1] + arr_1[size / 2]) / 2.0;
        return t;
    }
}

// bonus for median (different method)
// double median()
// {
//     double copy[MAX_SIZE];
//     for (int i = 0; i < size; i++)
//     {
//         copy[i] = arr[i];
//     }
//     for (int i = 0; i < size - 1; i++)
//     {
//         for (int j = i + 1; j < size; j++)
//         {
//             if (copy[j] < copy[i])
//             {
//                 double temp = copy[i];
//                 copy[i] = copy[j];
//                 copy[j] = temp;
//             }
//         }
//     }
//     if (size % 2 == 1)
//     {
//         return copy[size / 2];
//     }
//     else
//     {
//         return (copy[size / 2 - 1] + copy[size / 2]) / 2.0;
//     }
// }

// Main function
int main()
{
    char command[10];
    Help();
    while (1)
    {
        printf("\nEnter command: ");
        scanf("%s", command);
        if (strcmp(command, "set") == 0)
        {
            Set();
        }
        else if (strcmp(command, "min") == 0)
        {
            if (initialized)
            {
                printf("Min       : %10.4f\n", Minimum());
            }
            else
            {
                printf("Array not initialized. Use 'set' command first.\n");
            }
        }
        else if (strcmp(command, "max") == 0)
        {
            if (initialized)
            {
                printf("Max       : %10.4f\n", Maximum());
            }
            else
            {
                printf("Array not initialized. Use 'set' command first.\n");
            }
        }
        else if (strcmp(command, "mean") == 0)
        {
            if (initialized)
            {
                printf("Mean      : %10.4f\n", Mean());
            }
            else
            {
                printf("Array not initialized. Use 'set' command first.\n");
            }
        }
        else if (strcmp(command, "stddev") == 0)
        {
            if (initialized)
            {
                double mean = Mean();
                printf("Std Dev   : %10.4f\n", Standard_deviation(mean));
            }
            else
            {
                printf("Array not initialized. Use 'set' command first.\n");
            }
        }
        else if (strcmp(command, "hist") == 0)
        {
            histogram();
        }
        else if (strcmp(command, "summary") == 0)
        {
            if (initialized)
            {
                double mean = Mean();
                printf("Min       : %10.4f\n", Minimum());
                printf("Max       : %10.4f\n", Maximum());
                printf("Mean      : %10.4f\n", mean);
                printf("Std Dev   : %10.4f\n", Standard_deviation(mean));
                printf("Median    : %10.4f\n", median());
            }
            else
            {
                printf("Array not initialized. Use 'set' command first.\n");
            }
        }
        else if (strcmp(command, "median") == 0)
        {
            if (initialized)
            {
                printf("Median    : %10.4f\n", median());
            }
            else
            {
                printf("Array not initialized. Use 'set' command first.\n");
            }
        }
        else if (strcmp(command, "help") == 0)
        {
            Help();
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
    return 0;
}