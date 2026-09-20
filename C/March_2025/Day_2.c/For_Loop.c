#include <stdio.h>
int main()
{
   int i, n;
   printf("Enter value:");
   scanf("%d", &n);
   for (i = 0; i <= n; i += 1)
   {
      printf("%d ", i);
   }
   return 0;
}