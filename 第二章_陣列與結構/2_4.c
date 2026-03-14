#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
//結構體的「大小」與「位置」必須符合它成員中「最大型態」的倍數。
typedef struct
{
    int year;
    int month;
    int day;
} date; //因為我沒有要直接使用該結構 所以這樣寫可直接在human引用date

typedef struct 
{
    enum {female,male} sex;
    union
    {
        int childern;
        int beard;
    } u;
} sextype;

struct human  //引用時要寫struct human x;
{
    char name[10];
    int age;
    float salary;
    date birthday;
    sextype sexInfo;
};

int main(){
    struct human a;
    strcpy(a.name,"Mark"); //C不支援一整塊陣列附值
    a.age = 34;
    a.salary = 60000;
    a.birthday.year = 1991;
    a.birthday.month = 10;
    a.birthday.day = 8;
    a.sexInfo.sex = male;
    a.sexInfo.u.beard = FALSE;

    struct human b;
    strcpy(b.name,"Mary");
    b.age = 18;
    b.salary = 23000;
    b.birthday.year = 2004;
    b.birthday.month = 11;
    b.birthday.day = 18;
    b.sexInfo.sex = female;
    b.sexInfo.u.childern = 4;

    if(strcmp(a.name,b.name)){ //strcmp是比對 不同為true
        printf("different person");
        return FALSE;
    }
    if(a.age!=b.age){  
        printf("different person");
        return FALSE;
    }
    if(a.salary!=b.salary){  
        printf("different person");
        return FALSE;
    }
    printf("same person");
    return TRUE;
}