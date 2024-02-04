#include "tools.h"		//头文件

extern const ctools_menu CT_MENU;

#define FILE_INPUT  "./Brain-Fuck/input.txt"
#define FILE_OUTPUT "./Brain-Fuck/output.txt"

enum CODE_TYPE { CODE_INPUT = 0, CODE_FILE };

/* 删除文件夹 */
void delet_dir();
/* 执行代码 */
void code(int type, char filename[]);
/* 帮助 */
void help();

/* 读取输入 */
char *Input();
/* 读取文件 */
char *readfile(char *filename);
