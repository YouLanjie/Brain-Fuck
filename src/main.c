#include "../include/head.h"
#include <curses.h>

int main(int argc,char * argv[]) {
	int input = 0;
	int m = 1;
	menuData data = menuDataInit();

	data.title = "首页";
	data.addText(&data, "1.执行代码", "2.执行上一次", "3.程序帮助", "4.删除临时文件", "0.退出", NULL);
	data.addTextData(&data, 0, "%s%s%s%s%s", "%z本程序是由%zC%z语言编写成的%zbrain fuck%z语言解释器\n该选项会执行由%zbrain fuck%z语言编写的程序，其内容会以文本形式保存在临时文件内。你可以使用文本编辑器编辑，或者可以直接在终端调用该程序时加上你想要解析（执行）的文件名作为参数，该程序会读取传入的文件，而且支持解释多个文件%z", "%z这会读取上一次执行的程序留下的临时文件并自动执行，倘若没有临时文件则会报错%z", "%z查看程序的帮助条例%z", "%z移除程序的临时文件%z", "%z退出程序%z");

	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			Clear
			code(1,argv[count]);
		}
		return 0;
	}
	Clear2
	while (input != 0x30) {
		input = data.menuShow(&data);
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
				endwin();
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
					endwin();
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
	endwin();
	return 0;
}

