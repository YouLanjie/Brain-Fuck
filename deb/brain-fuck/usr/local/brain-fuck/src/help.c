#include "../include/head.h"

void help() {
	char a = 0x00;
	char b = 1;

	while (a == 0x00) {
		Clear2
		menu2("帮助");
		printf("\033[2;32m\033[6;26H↑\033[10;26H↓\033[0m");
		printf("\033[1;33m");
		kbhit2();
		if (b == 1) {
			printf("\033[7;5H1.↑上翻，↓下翻");
			printf("\033[8;5H2.输入代码时按下Esc退出");
			printf("\033[9;5H3.存储条只有500个");
		}
		else if (b == 2) {
			printf("\033[7;5H4.历史功能直接读取文件信息，不用再次输入");
			printf("\033[8;5H5.主界面按下9删除文件");
			printf("\033[9;5H6.可以执行其他文件，格式\"brain-fuck filename\"");
		}
		else if (b == 3) {
			printf("\033[7;5H7.执行程序时按下任意按键退出");
			printf("\033[8;5H8.执行程序时同时会保存输出");
			printf("\033[9;5H9.不要将窗口缩小到比程序界面还要小");
		}
		printf("\033[11;52H\033[2;32m%d/3\033[1;33m",b);
		Menu2
		a = input();
		if (a == 0x1B) {
			if (kbhit_if() == 1) {
				getchar();
				a = getchar();
				if (a == 0x41 || a == 0x44) {
					if (b > 1) {
						b--;
					}
					else {
						printf("\a");
					}
				}
				else if (a == 0x42 || a == 0x43) {
					if (b < 3) {
						b++;
					}
					else {
						printf("\a");
					}
				}
				a = 0x00;
			}
			else {
				printf("\033[0m");
				Clear
				return;
			}
		}
		Clear
	}
	Clear
	return;
}

