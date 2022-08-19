#include "../include/head.h"

void help() {
	menuData help = menuDataInit();

	help.title = "首页";
	help.cfg   = 2;
	help.addText(&help,
			"1.%z↑上翻，↓下翻%z",
			"2.%z输入代码时按下%zEsc%z退出%z",
			"3.%z存储条只有%z500%z个%z",
			"4.%z历史功能直接读取文件信息，不用再次输入%z",
			"5.%z主界面按下%z9%z删除文件%z",
			"6.%z可以执行其他文件，格式%z\"brain-fuck filename\"",
			"7.%z执行程序时按下任意按键退出%z",
			"8.%z执行程序时同时会保存输出%z",
			"9.%z不要将窗口缩小到比程序界面还要小%z",
			"7.%z输入执行代码时先回车再输入还可以显示内存条的状态、数值，方便调试程序%z",
			NULL);

	Clear2
	help.menuShow(&help);
	Clear2
	return;
}

