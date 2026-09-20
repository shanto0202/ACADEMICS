#include<stdio.h>

int main(){
    int x;
    char ch;
    float float_var;
    printf("enter a number:");
    scanf ("%d %c", &x,&ch);
    printf ("Your entered number is %d  and char= %c",x,ch);

    int a,b,result;
    printf ("Enter value:\t");
    scanf ("%d %d", &a, &b);
    result=a+b;
    printf ("sum= %d",result); 

	int x;
	char ch;
	float floart_var;
	printf("enter a number:");
	scanf ("%d %c",&x,&ch);
	printf ("Your entered number is %d  and char= %c",x,ch);


	int a,b,result;
	printf ("Enter value:\t");
	scanf ("%d %d", &a, &b);
	result=a+b;
	printf ("sum= %d\n",result);
	result=a-b;
	 printf ("substract= %d\n",result);
	 result=a/b;
	 printf ("division= %d\n",result);
	 result=a*b;
	 printf ("multiplication= %d",result);
	 
	if(a>b) {
	    	printf("%d is greater than %d\n",a,b);
		printf("if is called");
	}
	else {
    printf("%d is greater than %d\n",b,a);
    printf("else is called");
    
	}
}