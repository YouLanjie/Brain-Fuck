#include "../include/head.h"

/* 运行 */
static int running(char *ch, FILE *fp);
/* 显示界面 */
static void msg(unsigned int ram[500], unsigned short i, int status);

void code(int type, char filename[])
{/*{{{*/
	char *ch = NULL;
	FILE *fp = NULL;
	int stat = 0;

	if (type == CODE_INPUT) {
		/* 创建输入缓存 */
		mkdir("Brain-Fuck", 0744);
		/* 获取输入 */
		ch = Input();
		fp = fopen(FILE_OUTPUT, "wb");
		if (!fp) {
			attron(COLOR_PAIR(3));
			printw("错误[Error]: 无法创建输出记录文件");
			attroff(COLOR_PAIR(3));
			refresh();
			getch();
		}
	} else {
		attron(COLOR_PAIR(3));
		ch = readfile(filename);
		attroff(COLOR_PAIR(3));
		if (ch == NULL) {
			refresh();
			getch();
			return;
		}
	}
	move(0, 0);
	def_prog_mode();
	endwin();

	stat = running(ch, fp);
	if (stat < 0) {
		printf("错误[Error]: %s: %s[Code:%d]\n", filename, "循环括号不匹配", stat);
		if (type == CODE_FILE)
			return;
		reset_prog_mode();
		refresh();
		clear();
		attron(COLOR_PAIR(3));
		printw("错误[Error]: %s: %s[Code:%d]\n", filename, "循环括号不匹配", stat);
		attroff(COLOR_PAIR(3));
		refresh();
		getch();
		return;
	}
	/* asdfaeqoifajsdfk */
	printf("\n\033[44m程序结束\n按下任意键继续\033[0m\n");
	ctools_getch();
	if (fp)
		fclose(fp);
	if (type == CODE_FILE)
		return;
	reset_prog_mode();
	clear();
	return;
}/*}}}*/

/* 待处理字符 */
#define chp ch[i_c]
/* 确保指针不越界的安全条件 */
#define chs (ch[i_c] != '\0')

static int running(char *ch, FILE *fp)
{/*{{{*/
	unsigned int ram[500] = {0},	/*用于存储内存数据 */
		     i_r = 0,	/* 表示模拟的指针所指的内存序号 */
		     i_c = 0;	/* 输入字符指针号 */
	int flag_while = 0,	/* 循环层级标记 */
	    flag_count = 0,	/* 循环符号标记 */
	    flag_step = 0,	/* 调试用单步执行 */
	    mode = 0;	/* 模式 */
	int inp = 0;

	if (ch[0] == '\n')
		mode = 1;
	while (ch[i_c] != '\0') {
		if (flag_step) {
			inp = ctools_getch();
			if (inp == 'p' || inp == ' ')
				flag_step = 0;
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
				return -3;
			break;
		case ']':	//"]"循环结束
			flag_count--;
			if (flag_count < 0)
				return -1;
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
				return -2;
			flag_while--;
			continue;
			break;
		case '.':	//"."显示
			printf("%c", ram[i_r]);
			if (fp)	//将输出记录到文件里面
				fprintf(fp, "%c", ram[i_r]);
			ctools_kbhitGetchar();	//将缓存区的内容写入到文件里
			msg(ram, i_r, mode);
			ctools_kbhitGetchar();
			break;
		case ',':	//","输入
			ram[i_r] = getch();
			msg(ram, i_r, mode);
			break;
		case '<':	//"<"左移
			i_r = (i_r <= 0) ? 499 : i_r - 1;
			msg(ram, i_r, mode);
			break;
		case '>':	//">"右移
			i_r = (i_r >= 499) ? 0 : i_r + 1;
			msg(ram, i_r, mode);
			break;
		case '-':	//"-"减
			ram[i_r] = (ram[i_r] <= 0) ? 259 : ram[i_r] - 1;
			msg(ram, i_r, mode);
			break;
		case '+':	//"+"加
			ram[i_r] = (ram[i_r] >= 259) ? 0 : ram[i_r] + 1;
			msg(ram, i_r, mode);
			break;
		default:	//其他跳过
			break;
		}
		if (ctools_kbhit() == 1) {
			inp = getchar();
			if (inp == 'p' || inp == ' ') {
				printf("<Paused> Press any return\n");
				ctools_getch();
			} else if (inp == 'n') {
			} else {
				return 1;
			}
		}
		i_c++;
	}
	return 0;
}/*}}}*/

static void msg(unsigned int ram[500], unsigned short i, int status)
{/*{{{*/
	if (status != 1) {
		return;
	}
	printf("\033[s\033[5;1H");
	for (int count = -5; count < 7; count++) {
		int tmp = i + count;
		tmp = (tmp >= 0) ? tmp % 500 : tmp + 500;
		printf("%s[%3d]%s", count == 0 ? "\033[44m": "", tmp,
		       count == 0 ? "\033[0m": "");
	}
	printf("\n");
	for (int count = -5; count < 7; count++) {
		int tmp = i + count;
		tmp = (tmp >= 0) ? tmp % 500 : tmp + 500;
		if (count == 0)
			printf("\033[44m");
		printf("%s[%3d]%s", count == 0 ? "\033[44m": "", ram[tmp],
		       count == 0 ? "\033[0m": "");
	}
	printf("\n");
	printf("\033[u");
	/*usleep(1000000 / 20);*/
	return;
}/*}}}*/
