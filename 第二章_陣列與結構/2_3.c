#include <stdio.h>
#include <stdlib.h> // 必須引入，才有 malloc

// 定義課本常用的 MALLOC 巨集，p是你要接收地址的指標。s是你要申請的空間大小。
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory\n"); \
        exit(EXIT_FAILURE); \
    }

// 跟malloc類似 但多了自動清理值的功能 跟MALLOC依樣會回傳址
#define CALLOC(p, n, s) \
    if (!((p) = calloc(n,s))) { \
        fprintf(stderr, "Insufficient memory\n"); \
        exit(EXIT_FAILURE); \
    }

// 擴充
#define REALLOC(p, s) \
    if (!((p) = realloc(p,s))) { \
        fprintf(stderr, "Insufficient memory\n"); \
        exit(EXIT_FAILURE); \
    }

int** make2dArray(int rows, int cols) {
    int **x, i; //int** x,i跟int **x,i意思是依樣的  **x是真實的值 *x是真實值的地址 x是地址的地址
    
    // 第一層：分配「指標陣列」的空間（存地址）
    // MALLOC(x, rows * sizeof(*x));  //先放row位置 比如0~100
    CALLOC(x, rows , sizeof(*x));

    // 第二層：分配「整數陣列」的空間（存真正的值）
    for(i = 0; i < rows; i++) {
        //MALLOC(x[i], cols * sizeof(**x)); //之後才放cols位置 101~1000
        CALLOC(x[i], cols , sizeof(**x));
    }
    
    return x;
}

int main() {
    int rows = 3, cols = 4;
    int **myArray = make2dArray(rows, cols);

    // 測試存取
    //myArray[0][0] = 99;  //若用CALLOC的話 不附值就會是0
    printf("Value at [0][0]: %d\n", myArray[0][0]);
    printf("myArray is %d\n",myArray); // 用malloc跟heap申請的起始位置
    printf("&myArray is %d\n",&myArray);  //stack上myArray的位置
    printf("*myArray is %d\n",*myArray); // heap上 row的起始位置
    printf("**myArray is %d\n",**myArray); 

    // 注意：用完要記得釋放記憶體！
    return 0;
}