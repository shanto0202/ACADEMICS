#include <stdio.h>
#include <windows.h> // For Sleep()

int main()
{
    int h, m, s;
    char period[3]; // "AM" or "PM"

    // Take current time from the user in 12-hour format
    printf("Enter current time (HH MM SS AM/PM): ");
    scanf("%d %d %d %2s", &h, &m, &s, period);

    // Convert to uppercase for safety
    if (period[0] >= 'a' && period[0] <= 'z')
        period[0] -= 32;
    if (period[1] >= 'a' && period[1] <= 'z')
        period[1] -= 32;

    // Validate input
    if (h < 1 || h > 12 || m < 0 || m > 59 || s < 0 || s > 59 ||
        !((period[0] == 'A' && period[1] == 'M') || (period[0] == 'P' && period[1] == 'M')))
    {
        printf("Invalid time format!\n");
        return 1;
    }

    while (1)
    {
        // Print the time
        printf("%02d:%02d:%02d %s", h, m, s, period);
        fflush(stdout);
        Sleep(1000);

        // Move cursor back for overwrite
        for (int i = 0; i < 11; i++)
        {
            printf("\b");
        }

        // Update time
        s++;
        if (s == 60)
        {
            s = 0;
            m++;
        }
        if (m == 60)
        {
            m = 0;
            h++;
        }
        if (h == 12 && m == 0 && s == 0)
        {
            // Switch AM/PM after 12:00:00
            if (period[0] == 'A')
                period[0] = 'P';
            else
                period[0] = 'A';
        }
        if (h == 13)
        {
            h = 1;
        }
    }

    return 0;
}
