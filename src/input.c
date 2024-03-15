#include "../include/head.h"

struct Inp_s {
	int ch;
	struct Inp_s *pNext;
};

/* 创建新节点并初始化 */
static struct Inp_s *Inp_new(void);

char *Input()
{				/*{{{ */
	struct Inp_s *pHead = NULL;
	struct Inp_s *pNew = NULL;
	struct Inp_s *pLast = NULL;
	pLast = pNew = pHead = Inp_new();

	int inp = 0;
	int count = 1;

	curs_set(2);
	clear();
	printw("请输入,按下ESC退出：\n");
	while (inp != 0x1B) {
		refresh();
		inp = getch();
		if (inp == 0x1B) {	/* <ESC> */
			inp = (kbhit() == 0) ? 0x1B : getchar()
			    && getchar();
			continue;
		} else if (inp == 0x7F) {	/* <Backspace> */
			if (pNew == pHead)
				continue;
			count--;
			free(pNew);
			pLast->ch = 0;
			pLast->pNext = NULL;

			clear();
			printw("请输入,按下ESC退出：\n");
			pNew = pLast;
			if (pLast == pHead)	/* H,L;N */
				continue;
			pNew = pHead;
			while (pNew->pNext != NULL) {
				printw("%c", pNew->ch);
				pLast = pNew;
				pNew = pNew->pNext;
			}
			continue;
		}
		if (inp == '\r') {
			inp = '\n';
		}
		printw("%c", inp);
		pLast = pNew;
		pNew->ch = inp;
		pNew = Inp_new();
		pLast->pNext = pNew;
		count++;
	}
	curs_set(0);
	clear();
	pNew = pHead;
	char *ch = malloc(sizeof(char)*count);
	for (int i = 0; i < count; i++) {
		ch[i] = pNew->ch;
		pNew = pNew->pNext;
	}
	free(pHead);
	return ch;
}				/*}}} */

char *readfile(char *filename)
{				/*{{{ */
	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		return NULL;
	}
	long size = 0L;
	fseek(fp, 0L, 2);
	size = ftell(fp);
	fseek(fp, 0L, 0);
	char *ch = malloc(sizeof(char) * (size + 1));
	fread(ch, 1, size, fp);
	fclose(fp);
	return ch;
}				/*}}} */

static struct Inp_s *Inp_new(void)
{				/*{{{ */
	struct Inp_s *p = (struct Inp_s *)malloc(sizeof(struct Inp_s));
	p->pNext = NULL;
	p->ch = 0;
	return p;
}				/*}}} */
