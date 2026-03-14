#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100 // 全域陣列最大容量

// 1. 定義多項式的結構(term是項)
typedef struct {
    float coef; // 係數 (Coefficient)
    int degree;  // 指數 (degree)
} poly_term;

poly_term terms[MAX_TERMS];
int avail = 0; // 指向陣列中下一個空位

int compare(int a, int b) {
    if (a > b) return 1;
    else if (a == b) return 0;
    else return -1;
}

// 將新項接到結果後方 (Attach) ---
void attach(float coefficient, int degree) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "錯誤：多項式項數超過上限！\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail].degree = degree;
    avail++;
}

// 傳入 A, B 的起始與結束位置，並透過指標回傳 D 的範圍
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
    float sum;
    *startD = avail; // D 的起始位置就是目前可用的空位

    // 對應虛擬碼的 while (! IsZero(a) && ! IsZero(b))
    while (startA <= finishA && startB <= finishB) {
        switch (compare(terms[startA].degree, terms[startB].degree)) {
            case 1: // a 的次數較大
                attach(terms[startA].coef, terms[startA].degree);
                startA++;
                break;
                
            case 0: // 次數相同，係數相加
                sum = terms[startA].coef + terms[startB].coef;
                if (sum != 0) { // 如果相加不為 0 才需要存入
                    attach(sum, terms[startA].degree);
                }
                startA++;
                startB++;
                break;
                
            case -1: // b 的次數較大
                attach(terms[startB].coef, terms[startB].degree);
                startB++;
                break;
        }
    }

    // 對應虛擬碼的 insert any remaining terms (收尾)
    for (; startA <= finishA; startA++) {
        attach(terms[startA].coef, terms[startA].degree);
    }
    for (; startB <= finishB; startB++) {
        attach(terms[startB].coef, terms[startB].degree);
    }

    *finishD = avail - 1; // 標記 D 的結束位置
}

// --- 輔助函式：列印多項式 ---
void printPoly(int start, int finish) {
    for (int i = start; i <= finish; i++) {
        printf("%.1fx^%d", terms[i].coef, terms[i].degree);
        if (i < finish) printf(" + ");
    }
    printf("\n");
}

int main() {
    // 建立多項式 A = 2x^1000 + 1
    int startA = avail;
    terms[avail].coef = 2.0; terms[avail].degree = 1000; avail++;
    terms[avail].coef = 1.0; terms[avail].degree = 0;    avail++;
    int finishA = avail - 1;//減1才是真正的最後一位

    // 建立多項式 B = 1x^4 + 10x^3 + 1
    int startB = avail;
    terms[avail].coef = 1.0;  terms[avail].degree = 4; avail++;
    terms[avail].coef = 10.0; terms[avail].degree = 3; avail++;
    terms[avail].coef = 1.0;  terms[avail].degree = 0; avail++;
    int finishB = avail - 1;

    int startD, finishD;

    printf("A: "); printPoly(startA, finishA);
    printf("B: "); printPoly(startB, finishB);

    // 執行相加邏輯
    padd(startA, finishA, startB, finishB, &startD, &finishD);

    printf("D: "); printPoly(startD, finishD);

    return 0;
}
