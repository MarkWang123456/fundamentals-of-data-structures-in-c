#include <stdio.h>

#define MAX_TERMS 101
#define MAX_COL 101 // 必須定義最大行數以建立輔助陣列
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

void fast_transpose(term x[], term y[]) {
    int row_terms[MAX_COL], //統計原矩陣中，每一Col有多少個非零資料
    starting_pos[MAX_COL];//starting_pos是每一col的資料在轉置後的陣列中，應該從哪一格開始放
    int i, j, num_cols = x[0].col, num_terms = x[0].value;

    y[0].row = num_cols;
    y[0].col = x[0].row;
    y[0].value = num_terms;

    if (num_terms > 0) {
        for (i = 0; i < num_cols; i++) {// 初始化 row_terms
            row_terms[i] = 0;
        }

        for (i = 1; i <= num_terms; i++) {// 統計原矩陣每一行 (col) 出現的次數
            row_terms[x[i].col]++; //每出現一次行號就+1  如果 a[i].col 是 3，那這行程式碼就相當於 row_terms[3]++，也就是把第 3 行的計數器加 1。
        }
            
        starting_pos[0] = 1; // 資料從 Index 1 開始
        for (i = 1; i < num_cols; i++) { // 計算每一行在轉置後矩陣 b 中的起始位置
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
        }

        for (i = 1; i <= num_terms; i++) {  // 重頭掃描 a 陣列，直接投遞到 b 的正確位置
            j = starting_pos[x[i].col]++; // 取得位置後，該指標往後移一位
            y[j].row = x[i].col;
            y[j].col = x[i].row;
            y[j].value = x[i].value;
        }
    }
}


// 快速轉置是先安排好空間 
// 每一Col有多少資料的陣列A，轉置後要從哪開始放資料的陣列B
// 首先線將陣列A每個col的資料數歸零 之後跑回圈計算每個col的資料數
// 由於轉置後的稀疏陣列資料也是從1開始放 所以陣列B[0]是從1開始
// 之後每個陣列B[1]就開始排 B[i] = B[i - 1] + A[i - 1];
// B[i - 1]是因為要從上一個B開始 A[i - 1]是因為要知道上一個i有多少資料
// 準備好A跟B後 用for跑一次原始陣列 若遇到一筆資料，就直接根據它的 Col 查陣列 B 得到位置，放進新陣列後，再把陣列 B 的該位置往後移一格。
// 使用單迴圈 用空間換取時間 雖然空間使用較多但比較快

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
    fast_transpose(a,b);
    printf("Sparse Matrix b\n");
    print1(b);
    return 0;
}