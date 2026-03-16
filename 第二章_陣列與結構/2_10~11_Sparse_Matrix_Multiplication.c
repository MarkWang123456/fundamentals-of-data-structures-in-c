#include<stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_COL 101
#define COMPARE(a, b) ((a) < (b) ? -1 : ((a) == (b) ? 0 : 1))

typedef struct {
    int row;
    int col;
    int value;
} term;


term a[MAX_TERMS] = {
    {6, 6, 4},  
    {0, 3, 2}, 
    {2, 1, -5}, 
    {5, 0, 1},
    {5, 1, 9},
};

term b[MAX_TERMS] = {
    {6, 4, 4},
    {0, 1, 2},
    {1, 3, -3},
    {2, 2, 5},
    {3, 0, 7},
};

term d[MAX_TERMS];

void fast_transpose(term x[], term y[]) {//直接幹2_9的方法
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

//total_d 和 result的值會在mmult中不停變動 result 是暫存器,total_d 是計數器 所以要傳址
void storeSum(term d[], int *total_d, int row, int column, int *result)
{
    if (*result)
        if (*total_d < MAX_TERMS) {
            d[++(*total_d)].row = row;
            d[*total_d].col = column;
            d[*total_d].value = *result;
            *result = 0;
        }
        else {
            fprintf(stderr, "Numbers of terms in d exceed MAX_TERMS\n");
            exit(1); //要引用 <stdlib.h>
        }
}

void mmult(term a[], term b[], term d[])
{
    // A 的寬度必須等於 B 的高度
    if (a[0].col != b[0].row) {
        fprintf(stderr, "Incompatible matrices\n");
        exit(1);
    }

    term new_b[MAX_TERMS];  // b轉置後的稀疏矩陣
    fast_transpose(b, new_b);

    int i,j,
    total_d = 0,//相乘後陣列中不為零的數量
    row_begin = 1, 
    row_now = a[1].row,// 外迴圈從a[1].row開始
    col_now,//col_now 代表目前a的「列」正在與b的「哪一欄」進行運算
    result = 0;;
    int rows_a = a[0].row, total_a = a[0].value;
    int cols_b = b[0].col, total_b = b[0].value;
    
    // set boundary condition 在最後一項之後加入假資料，用來觸發最後一列的 storeSum
    a[total_a+1].row = rows_a;
    new_b[total_b+1].row = cols_b;
    new_b[total_b+1].col = 0;

    //利用雙迴圈比對 外圈用a的row跟內圈new_b的row比對 若當下兩邊的col都相同就相乘相加
    for (i = 1; i <= total_a; ) {// 控制權不在迴圈頭部，而是在迴圈內部的邏輯裡 所以不用++
        col_now = new_b[1].row;//必須放在這重置 col_now， a[i].col必須每次跟每個new_b[j].col比對
        for (j = 1; j <= total_b + 1; ) {
            /* 如果a的Row跟row_now不同時，代表這組乘法結束 */
            if (a[i].row != row_now) {
                storeSum(d, &total_d, row_now, col_now, &result);
                i = row_begin;
                // 如果當前的基準col_now跟的new_b第i個row依樣就j++ 直到跳出該row
                for (; new_b[j].row == col_now; j++); 
                col_now = new_b[j].row;
            }
            
            /* 如果 new_b 的 Row 變了（也就是 B 的 Col 變了） */
            else if (new_b[j].row != col_now) {
                storeSum(d, &total_d, row_now, col_now, &result);
                i = row_begin;
                col_now = new_b[j].row;
            }
            
            /* 核心對碰邏輯 */
            else switch (COMPARE(a[i].col, new_b[j].col)) {
                case -1: /* A 太前面，往後找 */
                    i++; break;
                case 0:  /* 對齊了！相乘加總 */
                    result += (a[i].value * new_b[j].value); //用+=累加 
                    i++; j++; break;
                case 1:  /* B 太前面，往後找 */
                    j++;
            }

        } 
        
        // 如果當前的基準row_now跟的a第i個row依樣就i++ 直到跳出該row
        for (; a[i].row == row_now; i++);
        row_begin = i; 
        row_now = a[i].row;//接下來基準從a第i個row開始
    } 
    
    // 最後填入結果矩陣d的規格
    d[0].row = rows_a;
    d[0].col = cols_b;
    d[0].value = total_d;
}


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
    mmult(a, b, d);
    printf("mult result b\n");
    print1(d);
    return 0;
}