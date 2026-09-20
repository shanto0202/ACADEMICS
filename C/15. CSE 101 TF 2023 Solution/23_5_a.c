#include<stdio.h>

int main(){
    int n = 6;
    for(int i = 1; i<=n+1; i++){
        for(int j = 1; j<=n; j++){
            printf("%c ", 'A' + (i+j-2)%n);
        }
        printf("\n");
    }
}