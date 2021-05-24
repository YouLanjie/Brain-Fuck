#include <stdio.h>                           //printf();fopen();fclose();remove();rename();
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>                          //rmdir();
#include <sys/stat.h>
#include <sys/types.h>

#include "kbhit_input.h"                     //无延迟输入
#include "menu.h"                            //菜单模板

#define Clear printf("\033[2J\033[1;1H");    //清屏，方便移植
#define Clear2 system("clear");              //清屏，方便移植

void welcome(int m);                         //开始界面
void code(int h,char filename[]);
void help();

void in();
void print();                               //读取文件并打印
void miss(unsigned short ram[500],unsigned short i);
