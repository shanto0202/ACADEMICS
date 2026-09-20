#include <stdio.h>
int main()
{
    int t, n, level = 0, level_1;
    scanf("%d", &t);
    for (int j = 1; j <= t; j++)
    {
        int s = 0, h = 0, b1 = 0, b2 = 0, b = 0, pm = 5, pl = 0, count = 0;
        scanf("%d", &n);
        if (n == 0)
        {
            printf("Row %d: INACTIVE - Energy Level 0\n", j);
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                int track = i;
                scanf("%d", &i);
                s = s + i;
                if (track % 2 != 0)
                {
                    h = h + i;
                    b1 = b1 + i;
                }
                else
                {
                    h = h - i;
                    b2 = b2 + i;
                }
                i = track;
            }
            // check h harmonic or not
            if (h % 7 == 0)
            {
                h = 4;
                count++;
            }
            else
            {
                h = 0;
            }
            // check balanced or not
            if (b1 == b2)
            {
                b = 2;
                count++;
            }
            // check s prime or not
            if (s == 0 || s == 1)
            {
                pm = 0;
            }
            else
            {
                for (int i = 2; i * i <= s; i++)
                {
                    if (s % i == 0)
                    {
                        pm = 0;
                        break;
                    }
                }
            }
            if (pm != 0)
            {
                count++;
            }
            // check s pallindrom or not
            int rem, rev = 0, num;
            num = s;
            while (s != 0)
            {
                rem = s % 10;
                rev = rev * 10 + rem;
                s = s / 10;
            }
            if (rev == num)
            {
                pl = 3;
                count++;
            }
            //check energy level
            level_1 = level;
            level = h + b + pm + pl;
            if (count == 0)
            {
                printf("Row %d: INACTIVE - Energy Level %d\n", j, level);
            }
            if (count == 1)
            {
                printf("Row %d: LOW - Energy Level %d\n", j, level);
            }
            if (count == 2)
            {
                printf("Row %d: MEDIUM - Energy Level %d\n", j, level);
            }
            if (count == 3)
            {
                printf("Row %d: HIGH - Energy Level %d\n", j, level);
            }
            if (count == 4)
            {
                printf("Row %d: ULTRA - Energy Level %d\n", j, level);
            }
            level = level_1 + level;
        }
    }
    printf("Total Energy: %d", level);
    return 0;
}