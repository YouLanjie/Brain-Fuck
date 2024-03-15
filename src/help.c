#include "../include/head.h"

void help() {
	cmenu help = cmenu_create();

	cmenu_set_title(help, "帮助 ");
	cmenu_set_type(help, "help");
	cmenu_add_text(help, 0,
		       "1.↑上翻，↓下翻\n"
		       "2.输入代码时按下Esc退出\n"
		       "3.存储条只有500个\n"
		       "4.历史功能直接读取文件信息，不用再次输入\n"
		       "5.主界面按下9删除文件\n"
		       "6.可以执行其他文件，格式\"brain-fuck filename\"\n"
		       "7.执行程序时按下任意按键退出\n"
		       "8.执行程序时同时会保存输出\n"
		       "9.不要将窗口缩小到比程序界面还要小\n"
		       "7.输入执行代码时先回车再输入还可以显示内存条的状态、数值，方便调试程序\n",
			NULL, NULL, NULL, NULL, 0, 0, 0);
	cmenu_show(help);
	return;
}

