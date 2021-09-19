#include "include.h"                         //头文件

struct InputStruct {
        int m;
        struct InputStruct * pNext;
};

/* 定义函数 */
void code(int h,char filename[]);
void help();

void print();                               //读取文件并打印
void miss(unsigned short ram[500],unsigned short i);

struct InputStruct * New();

