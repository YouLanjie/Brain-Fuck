#include "../include/head.h"

void miss(unsigned short ram[500],unsigned short i, int *status) {          //用于显示界面
	if (*status != 1) {
		return;
	}
	printf("\033[s\033[1;1H");
	kbhitGetchar();                                        //使输出起效果
	printf("\033[1;1H\033[34m---------------\033[33m--------------------------------------------------------------\033[0m\n");
	for (int count = -7; count < 9; count++) {
		if (i + count >= 0 && i + count < 500) {
			printf("\033[32m[%3d][%3d]    \033[34m|\033[33m\033[61C|\033[0m\n",i + count + 1,ram[i + count]);
		}
		else {
			if (i + count < 0) {
				printf("\033[32m[%3d][%3d]    \033[34m|\033[33m\033[61C|\033[0m\n",i + count + 500,ram[i + count + 499]);
			}
			else if (i + count >= 500) {
				printf("\033[32m[%3d][%3d]    \033[34m|\033[33m\033[61C|\033[0m\n",i + count - 499,ram[i + count - 500]);
			}
		}
	}
	printf("\033[34m---------------\033[33m--------------------------------------------------------------\033[0m\n");
	printf("\033[9;12H\033[2;31m<\033[0m\033[H\n");
	printf("\033[u");
	kbhitGetchar();
	return;
}
