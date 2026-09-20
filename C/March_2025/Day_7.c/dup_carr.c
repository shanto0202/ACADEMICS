#include <stdio.h>
int main()
{
 int n;
 scanf("%d",&n);
 int arr[n];
 for(int i = 0; i < n; i++)
 {
     scanf("%d",&arr[i]);
 }
 int dupLi[n],countDup=0;
for(int i = 0; i < n; i++)
{
    for(int j=i+1;j<n;j++){
        if(arr[i]==arr[j]){
            dupLi[countDup++]=arr[i];
          //  countDup++;
        }
        
    }
} 
for(int i = 0; i < countDup; i++)
{
    printf("%d ",dupLi[i]);
}
return 0;
}