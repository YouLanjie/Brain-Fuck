#include "tools.h"                         //头文件

struct InputStruct {
        int m;
        struct InputStruct * pNext;
};

/* 定义函数 */
void code(int h,char filename[]);
void help();

void miss(unsigned short ram[500],unsigned short i, int *status);
void pass(unsigned short ram[500],unsigned short i);          //用于占位，不作用

struct InputStruct * New();

