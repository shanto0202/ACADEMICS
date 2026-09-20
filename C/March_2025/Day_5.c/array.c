#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    // int arr[n];
    // for(int i=0;i<n;i++){
    //     scanf("%d",&arr[i]);//arr[i]=i*5;
    // }
    // for(int i=0;i<n;i++){
    //     printf("%d ",arr[i]);
    // }
    
    char sifat[n];
    // for (int i = 0; i < n-1; i++)
    // {
    // scanf(" %c",&charr[i]);
    // }
   // charr[n-1]='\0';
   scanf("%s",sifat);
   sifat[0]='A';
   for(int i=0;i<n;i++){
    printf("%c ",sifat[i]);
   }
   // printf("%s",sifat);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%c ", charr[i]);
    // }
    return 0;
}