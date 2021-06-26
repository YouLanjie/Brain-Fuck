#include "include.h"                         //头文件

struct Input {
        int m;
        struct Input * pNext;
};

/* 定义函数 */
void welcome(int m);                         //开始界面
void code(int h,char filename[]);
void help();

void print();                               //读取文件并打印
void miss(unsigned short ram[500],unsigned short i);

struct Input * New();

