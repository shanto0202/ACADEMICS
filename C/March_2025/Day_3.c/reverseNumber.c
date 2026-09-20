#include <stdio.h>
int rev( int n)
{
    int  temp, result=0, reminder;
   
    // printf("Enter n: ");
    // scanf("%d",&n);
    temp=n;
    while (temp != 0)
    {
     reminder= temp%10;
     result=reminder+result*10;
     temp=temp/10; 
    }
    return result;
}

int main()


{
    int n;//, temp, result=0, reminder;
   
    for(int i=0;i<5;i++){
        printf("Enter n: ");
        scanf("%d",&n);
        int p=rev(n);
        printf("The reversed number is %d", p);

    }
 
    // temp=n;
    // while (temp != 0)
    // {
    //  reminder= temp%10;
    //  result=reminder+result*10;
    //  temp=temp/10; 
    // }

    //x=reverse(n)
    return 0;
}