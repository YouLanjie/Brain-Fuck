#include "../include/head.h"

void help() {
	ctools_menu_t * help = NULL;

	ctools_menu_t_init(&help);

	help->title = "首页";
	help->cfg   = ctools_menu_Type_Help;
	ctools_menu_AddText(help,
			"1.↑上翻，↓下翻",
			"2.输入代码时按下Esc退出",
			"3.存储条只有500个",
			"4.历史功能直接读取文件信息，不用再次输入",
			"5.主界面按下9删除文件",
			"6.可以执行其他文件，格式\"brain-fuck filename\"",
			"7.执行程序时按下任意按键退出",
			"8.执行程序时同时会保存输出",
			"9.不要将窗口缩小到比程序界面还要小",
			"7.输入执行代码时先回车再输入还可以显示内存条的状态、数值，方便调试程序",
			NULL);

	ctools_menu_Show(help);
	return;
}

