#include <stdio.h>

#define MAX_SIZE 100
float sum(float [], int);
float input[MAX_SIZE], anwser;
int i;
void main(){
    for(i = 0 ; i<MAX_SIZE ; i++){
        input[i] = i;
    }
    anwser = sum(input,MAX_SIZE); //input等同&input[0]
    printf("The sum is : %f\n",anwser);
}
float sum(float list[],int a){
    int i;
    float tempsum = 0;
    for (i = 0; i < a; i++){
        tempsum += list[i];
    }
    return tempsum;
}