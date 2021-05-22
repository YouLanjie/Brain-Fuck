#include <stdio.h>                           //标准库
#include <stdlib.h>                          //system();srand();rand();malloc();free();
#include <string.h>                          //strcmp();
#include <unistd.h>
#include <time.h>

#include "kbhit_input.h"                     //无延迟输入
#include "menu.h"                            //菜单模板

#define Clear printf("\033[2J\033[1;1H");    //清屏，方便移植
#define Clear2 system("clear");              //清屏，方便移植

void welcome();                              //开始界面
void code(int h);
void help();

void in();
void print(int b);                           //读取文件并打印
