#include "tools.h"                         //头文件

extern const ctools_menu CT_MENU;

#define FILE_INPUT  "./Brain-Fuck/input.txt"
#define FILE_OUTPUT "./Brain-Fuck/output.txt"

struct InputStruct {
        int m;
        struct InputStruct * pNext;
};

/* 删除文件夹 */
void delet_dir();
/* 显示 */
void msg(unsigned short ram[500],unsigned short i, int *status);
/* 输入 */
struct InputStruct * New();
/* 执行代码 */
void code(int h,char filename[]);
/* 帮助 */
void help();

