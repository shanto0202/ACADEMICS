#include<stdio.h>

int findTraillingZero(int n){
    int zeros = 0;
    unsigned m = 1;
    while(!(m&n)){
        zeros++;
        m = m<<1;
    }
    return zeros;
}

int main(){
    int n;
    scanf("%d", &n);
    printf("%d", findTraillingZero(n));
    return 0;
}