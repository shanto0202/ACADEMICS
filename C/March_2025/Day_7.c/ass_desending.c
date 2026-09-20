#include <stdio.h>
int main()
{
    int n, asc = 0, des = 0, uns = 0;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);     
    }
    if (arr[0] < arr[1])
    {
        //if (des && arr[])
        des=1;
    }
    if(arr[0] > arr[1]){
        asc=1;
    }
    for (int i = 1; i < n-1; i++)
    {
       
        if(des && arr[i]>arr[i+1])
        {
            uns=1;
            break;
        }
        else if (asc && arr[i]<arr[i+1])
        {
            uns=1;
            break;
        }
    }
    if(uns){
        printf("Unsorted\n");
    }else{
        printf("Sorted\n");
    }
    return 0;
}