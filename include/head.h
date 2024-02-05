#include "tools.h"		//头文件

#define FILE_INPUT  "./Brain-Fuck/input.txt"
#define FILE_OUTPUT "./Brain-Fuck/output.txt"

enum CODE_TYPE { CODE_INPUT = 0, CODE_LAST, CODE_FILE };

extern int flag_file;

/* 删除文件夹 */
void delet_dir();
/* 执行代码 */
int code(int type, char filename[]);
/* 帮助 */
void help();
/* 设置 */
void settings();

/* 读取输入 */
char *Input();
/* 读取文件 */
char *readfile(char *filename);
