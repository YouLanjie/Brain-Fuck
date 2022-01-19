#include "../include/head.h"

void help() {
	char a = 0x00;
	char b = 1;
	struct winsize size;
	int startSize = 0;

	while (a == 0x00) {
		Clear2
		printf("\033[1;33m");
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		startSize = size.ws_col / 2 - 20;
		kbhitGetchar();
		if (b == 1) {
			printf("\033[7;%dH1.↑上翻，↓下翻", startSize);
			printf("\033[8;%dH2.输入代码时按下Esc退出", startSize);
			printf("\033[9;%dH3.存储条只有500个", startSize);
		}
		else if (b == 2) {
			printf("\033[7;%dH4.历史功能直接读取文件信息，不用再次输入", startSize);
			printf("\033[8;%dH5.主界面按下9删除文件", startSize);
			printf("\033[9;%dH6.可以执行其他文件，格式\"brain-fuck filename\"", startSize);
		}
		else if (b == 3) {
			printf("\033[7;%dH7.执行程序时按下任意按键退出", startSize);
			printf("\033[8;%dH8.执行程序时同时会保存输出", startSize);
			printf("\033[9;%dH9.不要将窗口缩小到比程序界面还要小", startSize);
		}
		Menu("帮助",b,3);
		printf("\033[20D                    ");
		Menu2("帮助");
		a = getch();
		if (a == 0x1B) {
			if (kbhit() == 1) {
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
