#include "../include/head.h"

struct InputStruct * New() {
	struct InputStruct * pHead = NULL;
	struct InputStruct * pNew,* pEnd;
	struct InputStruct * pTemp;

	int exit = 1;

	pEnd = pNew = pHead = (struct InputStruct *)malloc(sizeof(struct InputStruct));
	pHead -> pNext = NULL;
	pHead -> m = 0x00;

	curs_set(2);
	clear();
	printw("请输入：\n");
	do {
		if (pEnd -> m != 0) {
			pNew = (struct InputStruct *)malloc(sizeof(struct InputStruct));
			pNew -> pNext = NULL;
			pEnd -> pNext = NULL;
		}
		pNew -> m = getch();
		if (pNew -> m == 0x0D) {
			printw("\n");
		}
		else if (pNew -> m == 0x1B) {
			if (kbhit() == 0) {
				free(pNew);
				exit = 0;
			}
		}
		else if (pNew -> m == 0x7F) {
			free(pNew);
			if (pEnd == pHead) {
				if (pNew != pEnd) {
					free(pHead);
				}
				pEnd = pNew = pHead = (struct InputStruct *)malloc(sizeof(struct InputStruct));
				pHead -> pNext = NULL;
				pHead -> m = 0x00;
				printw("\n");
				Clear
				printw("请输入：\n");
				continue;
			}
			free(pEnd);
			printw("\n");
			Clear
			printw("请输入：\n");
			pTemp = pHead;
			while (pTemp -> pNext != NULL) {
				printw("%c",pTemp -> m);
				if (pTemp -> pNext == pEnd) {
					pTemp -> pNext = NULL;
					pEnd = pTemp;
					break;
				}
				pTemp = pTemp -> pNext;
			}
			pNew = NULL;
		}
		else {
			printw("%c",pNew -> m);
			pEnd -> pNext = pNew;
			pEnd = pNew;
		}
	}while (exit);
	curs_set(0);
	Clear
	if (pEnd == pHead) {
		pHead = NULL;
	}
	return pHead;
}
