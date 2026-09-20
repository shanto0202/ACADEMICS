#include<stdio.h>

#define m 5

int main(){
    FILE * fp = fopen("std_data.txt", "a+");
    int id;
    scanf("%d", &id);
    while(id!=0){
        fprintf(fp, "%d ", id);
        for(int i = 0; i<m;i++){
            int t ;
            scanf("%d", &t);
            fprintf(fp, "%d ", t);
        }
        fprintf(fp, "\n");
        scanf("%d", &id);
    }

    int search_id;
    printf("Enter a std id to find record: ");
    scanf("%d", &search_id);

    int total_std = 0;
    rewind(fp);
    while(1){
        char x;
        x = fgetc(fp);
        if(x==EOF){
            break;
        }else if(x == '\n'){
            total_std++;
        }
    }
    total_std;
    rewind(fp);
    int data[total_std][m+1];
    for(int i = 0; i<total_std; i++){
        for(int j = 0; j< m+1; j++){
            fscanf(fp, "%d", &data[i][j]);
        }
    }
    for(int i = 0; i<total_std; i++){
        if(data[i][0] ==search_id){
            int total = 0; 
            for(int j= 1; j<m+1; j++){
                total += data[i][j];
            }
            printf("total of the std: %d\n", total);
            break;
        }
    }
    printf("\nWhole data: \n");
    printf("for each std\n");
    for(int i = 0; i<total_std; i++){
        int total = 0;
        for(int j = 1; j<m+1; j++){
            total += data[i][j];
        }
        printf("Total of %d : %d\n", data[i][0], total);
    }

    printf("sub wise highest\n");

    for(int i = 1; i<m+1; i++){
        int h = 0;
        for(int j = 0; j<total_std ; j++){
            if(data[j][i] > h){
                h = data[j][i];
            }
        }
        printf("for sub %d: %d\n", i, h);
    }
    fclose(fp);
    return 0;
}