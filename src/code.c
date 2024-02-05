#include "../include/head.h"

/* 运行 */
static int running(int type, char *ch, FILE *fp);
/* 显示界面 */
static void msg(WINDOW *win, unsigned int ram[500], unsigned short i);

int code(int type, char filename[])
{/*{{{*/
	char *ch = NULL;
	FILE *fp = NULL;
	int stat = 0;

	if (type == CODE_INPUT) {
		/* 获取输入 */
		ch = Input();
		if (flag_file) {
			/* 创建输入缓存 */
			mkdir("Brain-Fuck", 0744);
			fp = fopen(FILE_INPUT, "w");
			if (!fp) {
				return -1;
			} else {
				fwrite(ch, 1, strlen(ch), fp);
				fclose(fp);
			}
			fp = fopen(FILE_OUTPUT, "w");
			if (!fp) {
				return -2;
			}
		}
	} else {
		ch = readfile(filename);
		if (ch == NULL)
			return -3;
	}

	stat = running(type, ch, fp);

	if (stat < 0) {
		return stat;
	}

	if (fp)
		fclose(fp);
	return 0;
}/*}}}*/

/* 待处理字符 */
#define chp ch[i_c]
/* 确保指针不越界的安全条件 */
#define chs (ch[i_c] != '\0')

static int running(int type, char *ch, FILE *fp)
{/*{{{*/
	struct ctools ctools = ctools_init();
	unsigned int ram[500] = {0},	/*用于存储内存数据 */
		     i_r = 0,	/* 表示模拟的指针所指的内存序号 */
		     i_c = 0;	/* 输入字符指针号 */
	int flag_while = 0,	/* 循环层级标记 */
	    flag_count = 0,	/* 循环符号标记 */
	    flag_step = 0,	/* 调试用单步执行 */
	    mode = 0;	/* 模式 */
	int inp = 0,    /* 检测输入 */
	    flag_exit = 0;

	if (ch[0] == '\n' && type != CODE_FILE)
		mode = 1;

	WINDOW *win1 = NULL,
	       *win2 = NULL;
	if (type != CODE_FILE) {
		if (mode) {
			win1 = newwin(LINES - 5, COLS, 0, 0);
			win2 = newwin(5, COLS, LINES - 5, 0);
			box(win2, 0, 0);
			wsetscrreg(win1, 0, LINES - 5);
		} else {
			win1 = stdscr;
			wsetscrreg(win1, 0, LINES);
		}
		wattron(win1, 252);
		wclear(win1);
	}

	while (ch[i_c] != '\0') {
		if (flag_step) {
			if (mode) {
				wmove(win2, 3, 2);
				wprintw(win2, "<Step:%c> Press 'p' or ' ' return", ch[i_c]);
				wrefresh(win2);
				inp = wgetch(win2);
			}
			if (type == CODE_FILE)
				inp = ctools.getcha();
			else if (!mode)
				inp = wgetch(win1);
			if (inp == 'p' || inp == ' ') {
				flag_step = 0;
				if (mode)
					wclear(win2);
					box(win2, 0, 0);
			}
		}
		switch (ch[i_c]) {
		case '[':	//"["循环开始
			flag_count++;
			if (ram[i_r] != 0) {
				flag_while++;
				break;
			}
			i_c++;
			for (int i = 1; chs && i > 0; i--) {
				for (; chs && chp != ']'; i_c++)
					if (chp == '[')
						i++;
				i_c++;
			}
			i_c--;
			if (!chs) 
				return -4;
			break;
		case ']':	//"]"循环结束
			flag_count--;
			if (flag_count < 0)
				return -4;
			if (flag_while <= 0)
				continue;

			i_c--;
			for (int i = 1; chs && i > 0; i--) {
				for (; chs && chp != '['; i_c--)
					if (chp == ']')
						i++;
				i_c--;
			}
			i_c++;
			if (!chs) 
				return -4;
			flag_while--;
			continue;
			break;
		case '.':	//"."显示
			if (type == CODE_FILE)
				printf("%c", ram[i_r]);
			else {
				wprintw(win1,"%c", ram[i_r]);
				wrefresh(win1);
			}
			if (fp)	//将输出记录到文件里面
				fprintf(fp, "%c", ram[i_r]);
			ctools.kbhitGetchar();	//将缓存区的内容写入到文件里
			msg(win2, ram, i_r);
			ctools.kbhitGetchar();
			break;
		case ',':	//","输入
			ram[i_r] = getch();
			msg(win2, ram, i_r);
			break;
		case '<':	//"<"左移
			i_r = (i_r <= 0) ? 499 : i_r - 1;
			msg(win2, ram, i_r);
			break;
		case '>':	//">"右移
			i_r = (i_r >= 499) ? 0 : i_r + 1;
			msg(win2, ram, i_r);
			break;
		case '-':	//"-"减
			ram[i_r] = (ram[i_r] <= 0) ? 259 : ram[i_r] - 1;
			msg(win2, ram, i_r);
			break;
		case '+':	//"+"加
			ram[i_r] = (ram[i_r] >= 259) ? 0 : ram[i_r] + 1;
			msg(win2, ram, i_r);
			break;
		default:	//其他跳过
			break;
		}
		if (ctools.kbhit() == 1) {
			inp = getchar();
			if (inp == 'p' || inp == ' ') {
				if (type == CODE_FILE) {
					printf("<Paused> Press any return\n");
					ctools.getcha();
				} else {
					if (mode){
						wmove(win2, 3, 2);
						wprintw(win2, "<Paused> Press any return");
						wrefresh(win2);
						wgetch(win2);
						wclear(win2);
						box(win2, 0, 0);
					} else {
						wgetch(win1);
					}
				}
			} else if (inp == 'n') {
				flag_step = 1;
			} else {
				flag_exit = 1;
				goto EXIT;
			}
		}
		i_c++;
	}
 EXIT:
	if (type == CODE_FILE) {
		printf("\n"
		       "\033[44m程序结束\033[0m\n"
		       "\033[44m按下任意键继续\033[0m\n");
		ctools.getcha();
	} else {
		if (!mode)
			win2 = win1;
		wattron(win2, COLOR_PAIR(252));
		wmove(win2, 3, 2);
		wprintw(win2, "程序结束,按下任意键返回");
		wattroff(win2, COLOR_PAIR(252));
		wrefresh(win2);
		wgetch(win2);
		if (mode) {
			delwin(win1);
			delwin(win2);
		}
		clear();
	}
	return flag_exit;
}/*}}}*/

static void msg(WINDOW *win, unsigned int ram[500], unsigned short i)
{				/*{{{ */
	if (win == NULL) {
		return;
	}
	wmove(win, 1, 2);
	for (int count = -5; count < 7; count++) {
		int tmp = i + count;
		tmp = (tmp >= 0) ? tmp % 500 : tmp + 500;
		if (count == 0)
			wattron(win, COLOR_PAIR(252));
		wprintw(win, "[%3d]", tmp);
		if (count == 0)
			wattroff(win, COLOR_PAIR(252));
	}
	wmove(win, 2, 2);
	for (int count = -5; count < 7; count++) {
		int tmp = i + count;
		tmp = (tmp >= 0) ? tmp % 500 : tmp + 500;
		if (count == 0)
			wattron(win, COLOR_PAIR(252));
		wprintw(win, "[%3d]", ram[tmp]);
		if (count == 0)
			wattroff(win, COLOR_PAIR(252));
	}
	wrefresh(win);
	/*usleep(1000000 / 20); */
	return;
}				/*}}} */
