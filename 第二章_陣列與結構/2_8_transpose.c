#include <stdio.h>

#define MAX_TERMS 101
typedef struct {
    int row;
    int col;
    int value;
} term;

term a[MAX_TERMS] = {
    {6, 6, 4},  
    {0, 3, 22}, 
    {2, 1, -5}, 
    {5, 0, 11},
    {5, 1, 99},
};

term b[MAX_TERMS];

void transpose(term a[],term b[]){//a轉置後放到b
    int n,i,j,currentb;
    n = a[0].value; //所有元素的個數
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;
    if(n>0) { //非零矩陣
        currentb = 1;//b的資料從1開始放
        for(i=0; i<a[0].col;i++) { //目前正在處理哪一col 從0(col)開始
            for(j=1;j<=n;j++){//掃描a中的所有元素(資料是從1開始)
                if(a[j].col==i){//如果被掃瞄到的元素剛好是目前正在處裡的第i row 則進行轉至
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;//往下放資料
                }
            }
        }
    }
}
// 普通轉置的流程是 外層迴圈是跑col 內層是跑所有的元素 若元素的col跟外圈依樣就轉置 
// 複雜度是O(cols*terms) 精隨在省空間但運行較慢

void print1(term x[]){
    int i;
    printf("     row  col  value\n");
    printf("_____________________________\n");
    for(i=0;i<=x[0].value;i++){
        printf("[%d]%5d%5d%5d\n",i,x[i].row,x[i].col,x[i].value);
    }
    printf("\n");
}

int main(){
    printf("Sparse Matrix a\n");
    print1(a);
    transpose(a,b);
    printf("Sparse Matrix b\n");
    print1(b);
    return 0;
}