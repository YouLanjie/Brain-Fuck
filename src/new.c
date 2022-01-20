#include "../include/head.h"
#include <stdio.h>

struct InputStruct * New() {
	struct InputStruct * pHead = NULL;
	struct InputStruct * pNew,* pEnd;
	struct InputStruct * pTemp;

	int exit = 1;

	pEnd = pNew = pHead = (struct InputStruct *)malloc(sizeof(struct InputStruct));
	pHead -> pNext = NULL;
	pHead -> m = 0x00;

	printf("\033[?25h请输入：\n");
	do {
		if (pEnd -> m != 0) {
			pNew = (struct InputStruct *)malloc(sizeof(struct InputStruct));
			pNew -> pNext = NULL;
			pEnd -> pNext = NULL;
		}
		pNew -> m = getch();
		if (pNew -> m == 0x0D) {
			printf("\n");
		}
		else if (pNew -> m == 0x1B) {
			if (kbhit() == 0) {
				free(pNew);
				printf("\033[?25l\n");
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
				printf("\n");
				Clear
				printf("请输入：\n");
				continue;
			}
			free(pEnd);
			printf("\n");
			Clear
			printf("请输入：\n");
			pTemp = pHead;
			while (pTemp -> pNext != NULL) {
				printf("%c",pTemp -> m);
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
			printf("%c",pNew -> m);
			pEnd -> pNext = pNew;
			pEnd = pNew;
		}
	}while (exit);
	printf("\n");
	Clear
	return pHead;
}
