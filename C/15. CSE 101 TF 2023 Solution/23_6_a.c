#include<stdio.h>

int countMinBits(unsigned n){
    unsigned m = 1;
    m = m << (8*sizeof(int)-1);
    int min_bits = 8*sizeof(int);
    while(!(m&n)){
        min_bits--;
        m = m>>1;
    }
    return min_bits;
}

int main(){
    unsigned n;
    scanf("%d", &n);
    printf("%d", countMinBits(n));
    return 0;
}