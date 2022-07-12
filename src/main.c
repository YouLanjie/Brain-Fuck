#include "../include/head.h"

int main(int argc,char * argv[]) {
	int input = 0;
	int m = 1;
	char *text[] = {
		"1.执行代码",
		"2.执行上一次",
		"3.程序帮助",
		"4.删除临时文件",
		"0.退出",
	};

	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			Clear
			code(1,argv[count]);
		}
		return 0;
	}
	Clear2
	printf("\033[?25l");
	while (input != 0x30) {
		printf("\033[1;33m");
		input = Menu("首页", text, 5, 2);
		m = 1;
		printf("\n");
		Clear2
		switch (input) {
			case 0x30:
			case 0x51:
			case 0x71:
			case 0x35:
				remove("./Brain-Fuck/input.txt");
				remove("./Brain-Fuck/output.txt");
				rmdir("./Brain-Fuck");
				printf("\033[?25h\n");
				Clear2
				return 0;
				break;
			case 0x1B:
				if (kbhit() == 1) {
					getchar();
					input = getchar();
					if (input == 0x41 || input == 0x44) {
						if (m > 1) {
							m--;
						}
						else {
							printf("\a");
						}
					}
					else if (input == 0x42 || input == 0x43) {
						if (m < 2) {
							m++;
						}
						else {
							printf("\a");
						}
					}
				}
				else {
					printf("\033[?25h");
					Clear2
					return 0;
					break;
				}
				break;
			case 0x31:
				code(0,"./Brain-Fuck/input.txt");
				break;
			case 0x32:
				code(1,"./Brain-Fuck/input.txt");
				break;
			case 0x33:
				help();
				break;
			case 0x34:
				remove("./Brain-Fuck/input.txt");
				remove("./Brain-Fuck/output.txt");
				rmdir("./Brain-Fuck");
				break;
			default:
				Clear
				break;
		}
		Clear
	}
	remove("./Brain-Fuck/input.txt");
	remove("./Brain-Fuck/output.txt");
	rmdir("./Brain-Fuck");
	printf("\033[?25h");
	Clear2
	return 0;
}

