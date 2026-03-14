#include <stdio.h>

int one[]={10,11,12,13,14};
void print1(int *ptr,int rows){
    int i;
    printf("address contents\n");
    for(i=0;i<rows;i++){
        printf("%8u%5d\n",ptr+i,*(ptr+i));
    }
    //印出的記憶體位置會跟陣列型態的大小有關 比如int就是4 double就是8
    printf("\n");
}
int main(){
    print1(one,5);
    printf("one is: %d\n", one);
    printf("one+1 is: %d\n", one+1);
    printf("&one+1 is: %d\n", &one+1);
    printf("*one+1 is: %d\n", *one+1);

    return 0;
}