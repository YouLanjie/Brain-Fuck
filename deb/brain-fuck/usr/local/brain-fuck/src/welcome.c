#include "../include/head.h"

void welcome(int m) {
	printf("\033[1;33m");
	if (m == 1) {
		printf("\033[8;11H0.退出程序\033[8;37H1.执行代码");
		printf("\033[9;11H2.执行上一次\033[9;37H3.程序帮助");
	}
	else if (m == 2) {
		printf("\033[8;11H4.执行外部文件\033[8;37H9.删除临时文件");
	}
	menu("首页",m,2);
	return;
}

