#include "include.h"                         //头文件

struct InputStruct {
        int m;
        struct InputStruct * pNext;
};

/* 定义函数 */
void code(int h,char filename[]);
void help();

void miss(unsigned short ram[500],unsigned short i, int *status);
void printbroid(const int status,unsigned short ram[500],unsigned short i);                               //读取文件并打印
void pass(unsigned short ram[500],unsigned short i);          //用于占位，不作用

struct InputStruct * New();

