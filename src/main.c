#include "../include/head.h"

int main(int argc,char * argv[]) {
	int input = 0;
	int m = 1;
	ctools_menu_t * data = NULL;

	ctools_menu_Init();
	ctools_menu_t_init(&data);
	
	data->title = "首页";
	ctools_menu_AddText(data,
			    "1.执行代码",
			    "2.执行上一次",
			    "3.程序帮助",
			    "4.删除临时文件",
			    "0.退出",
			    NULL);
	ctools_menu_AddTextData(data,
				ctools_menu_TextDataDescribe,
				"%s%s%s%s%s",
				"本程序是由C语言编写成的brain fuck语言解释器\n该选项会执行由brain fuck语言编写的程序，其内容会以文本形式保存在临时文件内。你可以使用文本编辑器编辑，或者可以直接在终端调用该程序时加上你想要解析（执行）的文件名作为参数，该程序会读取传入的文件，而且支持解释多个文件",
				"这会读取上一次执行的程序留下的临时文件并自动执行，倘若没有临时文件则会报错",
				"查看程序的帮助条例",
				"移除程序的临时文件",
				"退出程序");

	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			Clear;
			code(1,argv[count]);
		}
		return 0;
	}
	while (input != 0x30) {
		input = ctools_menu_Show(data);
		m = 1;
		printf("\n");
		Clear;
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
				if (ctools_kbhit() == 1) {
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
				Clear;
				break;
		}
		Clear;
	}
	remove("./Brain-Fuck/input.txt");
	remove("./Brain-Fuck/output.txt");
	rmdir("./Brain-Fuck");
	endwin();
	return 0;
}

