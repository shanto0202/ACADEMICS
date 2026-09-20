#include<stdio.h>
#include<stdlib.h>
char * strtok_own(char * str, char * delim){
    static char * s;
    if(str != NULL){
        s = str;
    }
    int f = -1, l, i = 0;
    while(s[i]){
        if(f == -1){
            int is_delim = 0, j = 0;
            while(delim[j]){
                if(delim[j] == s[i]){
                    is_delim = 1;
                    break;
                }
                j++;
            }
            if(!is_delim){
                f = i, l = i;
            }
        }else{
            int is_delim = 0, j = 0;
            while(delim[j]){
                if(s[i] == delim[j]){
                    is_delim = 1;
                    break;
                }
                j++;
            }
            if(is_delim){
                break;
            }else{
                l = i;
            }
        }
        i++;
    }
    if(f == -1){
        return NULL;
    }else{
        char * word = malloc(sizeof(char)*(l-f+2));
        int i;
        int  c = 0;
        for(i = f; i<=l; i++){
            word[c] = s[i];
            c++;
        }
        word[c] = '\0';
        for(int i = 0; i<=l; i++){
            int j = l-i;
            while(s[j] = s[j+1]){
                j++;
            }
        }
        return word;
    }
}
int main(){
    char str[] = "the name of our country is bangladesh. What is your name?";
    char * delim = " .?";
    char * p = strtok_own(str, delim);
    while(p!=NULL){
        printf("%s\n", p);
        p = strtok_own(NULL, delim);
    }
    printf("\n");
    char str2[] = " what is your name? Alice. Alice! Are you really Alice?!";
    char * delim2 = " ?.!";
    char * p2 = strtok_own(str2, delim2);
    while(p2!=NULL){
        printf("%s\n", p2);
        p2 = strtok_own(NULL, delim2);
    }
    return 0;
}