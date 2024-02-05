#include "../include/head.h"

static int deal_error(int type, char *filename);

int flag_file = 0;

int main(int argc, char *argv[])
{				/*{{{ */
	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			clear();
			deal_error(CODE_FILE, argv[count]);
		}
		return 0;
	}

	int input = 0;
	struct ctools_menu_t *data = NULL;
	struct ctools_menu m = ctools_init().menu;

	m.ncurses_init();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	m.data_init(&data);

	m.set_title(data, "首页");
	m.set_text(data,
		   "1.执行代码",
		   "2.执行上一次",
		   "3.程序帮助","4.程序设置", "5.删除临时文件", "0.退出", NULL);
	m.set_text_data(data, "describe", "%s%s%s%s%s%s",
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
			"关于设置",
			"移除程序的临时文件", "退出程序");

	while (input != 0x30) {
		input = m.show(data);
		clear();
		switch (input) {
		case 0:
		case 6:
			goto EXIT;
			break;
		case 1:
			deal_error(CODE_INPUT, FILE_INPUT);
			break;
		case 2:
			deal_error(CODE_LAST, FILE_INPUT);
			break;
		case 3:
			help();
			break;
		case 4:
			settings();
			break;
		case 5:
			delet_dir();
			break;
		default:
			break;
		}
		clear();
	}
 EXIT:
	endwin();
	return 0;
}				/*}}} */

static int deal_error(int type, char *filename)
{/*{{{*/
	int stat = code(type, filename);
	if (stat >= 0)
		return 0;
	if (type == CODE_INPUT)
		filename = "<INPUT>";

	type = (type == CODE_FILE) ? 0 : 1;
	char *error_list[] = {
		"无法打开输入文件",
		"无法打开输出文件",
		"无法打开文件！",
		"循环括号不匹配",
		"未知错误",
	};
	stat = (stat < -4) ? -5 : stat;
	if (type) {
		clear();
		attron(COLOR_PAIR(1));
		printw("[Error:%s::%d]: %s\n", filename, stat, error_list[-stat - 1]);
		attroff(COLOR_PAIR(1));
		printw("任意键返回\n");
		getch();
		return stat;
	}
	printf("\033[41m[Error:%s::%d]: %s\033[0m\n", filename, stat, error_list[-stat - 1]);
	return stat;
}/*}}}*/


void delet_dir()
{/*{{{*/
	remove("./Brain-Fuck/input.txt");
	remove("./Brain-Fuck/output.txt");
	rmdir("./Brain-Fuck");
	return;
}/*}}}*/
