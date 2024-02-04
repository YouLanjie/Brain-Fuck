#include "../include/head.h"

int main(int argc, char *argv[])
{
	int input = 0;
	struct ctools_menu_t *data = NULL;

	CT_MENU.ncurses_init();
	CT_MENU.data_init(&data);

	CT_MENU.set_title(data, "首页");
	CT_MENU.set_text(data,
			 "1.执行代码",
			 "2.执行上一次",
			 "3.程序帮助",
			 "4.删除临时文件", "0.退出", NULL);
	CT_MENU.set_text_data(data, "describe", "%s%s%s%s%s",
			      "本程序是由C语言编写成的brain fuck语言解释器\n"
			      "该选项会执行由brain fuck语言编写的程序，"
			      "其内容会以文本形式保存在临时文件内。"
			      "你可以使用文本编辑器编辑，"
			      "或者可以直接在终端调用该程序时加上你想要解析"
			      "（执行）的文件名作为参数，该程序会读取"
			      "传入的文件，而且支持解释多个文件",
			      /* ========================= */
			      "这会读取上一次执行的程序留下的临时文件并自动执行，"
			      "倘若没有临时文件则会报错",
			      /* ========================= */
			      "查看程序的帮助条例",
			      "移除程序的临时文件", "退出程序");

	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			clear();
			code(1, argv[count]);
		}
		goto EXIT;
	}

	while (input != 0x30) {
		input = CT_MENU.show(data);
		clear();
		switch (input) {
		case 0:
		case 5:
			goto EXIT;
			break;
		case 1:
			code(CODE_INPUT, FILE_INPUT);
			break;
		case 2:
			code(CODE_FILE, FILE_INPUT);
			break;
		case 3:
			help();
			break;
		case 4:
			delet_dir();
			break;
		default:
			break;
		}
		clear();
	}
 EXIT:
	delet_dir();
	endwin();
	return 0;
}

void delet_dir()
{
	remove("./Brain-Fuck/input.txt");
	remove("./Brain-Fuck/output.txt");
	rmdir("./Brain-Fuck");
	return;
}
