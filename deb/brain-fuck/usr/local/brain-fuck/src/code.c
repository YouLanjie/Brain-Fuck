#include "../include/head.h"
#include <sys/stat.h>

void code(int h,char filename[]) {
	struct Input * pTemp = NULL;

	long w[500];
	int a = 0;
	short ch = 0;
	unsigned short i = 0;
	unsigned short w1 = 0,q = 1,enter = 0;
	unsigned short ram[500];
	char wh = 0;

	FILE * fp,* fp2;

	mkdir("Brain-Fuck", 0744);
	fp = fopen(filename, "w");
	if(!fp) {
		perror("\033[1;31m[Code]\033[0m");
		input();
		return;
	}
	if (h == 0) {
		pTemp = New();
		while (pTemp != NULL) {
			fprintf(fp,"%c",pTemp -> m);
			pTemp = pTemp -> pNext;
		}
		fclose(fp);
		Clear2
	}
	fp = fopen(filename,"rb");
	if (!fp) {
		printf("\033[1;31m错误[Error]: %s: 没有那个文件或目录\a\033[0m\n",filename);
		input();
		return;
	}
	for (i = 0; i < 500; i++) {
		ram[i] = 0;
	}
	for (i = 0; i < 500; i++) {
		w[i] = 0;
	}
	i = 0;
	fp2 = fopen("./Brain-Fuck/output.txt","wb");
	if (!fp2) {
		printf("\033[1;31m错误[Error]: 当前目录无法创建文件，无法记录输出\a\033[0m\n");
		input();
	}
	miss(ram,i);
	printf("\033[3;16H");
	kbhit();
	while (a != EOF) {
		a = fgetc(fp);
		if (a == 0x5D && q == 0) {
			q = 1;
			continue;
		}
		if (q == 0) {
			continue;
		}
		switch (a) {
			case 0x5B:
				if (ram[i] != 0) {
					w[w1] = ftell(fp) - 1L;
					w1++;
					wh = 0;
				}
				else {
					q = 0;
				}
				break;
			case 0x5D:
				q = 1;
				if (w1 == 0) {
					Clear
					printf("\033[1;31m错误[Error]: %s: 循环括号不匹配\a\033[0m\n",filename);
					input();
					fclose(fp);
					return;
					break;
				}
				else {
					w1--;
				}
				fseek(fp,w[w1],0);
				if (wh == 0) {
					Clear
					printf("\033[1;31m错误[Error]: %s :循环内没有做任何有意义的动作\a\033[0m\n",filename);
					input();
					fclose(fp);
					return;
				}
				break;
			case 0x2E:
				printf("%c",ram[i]);
				if(fp2) {
					fprintf(fp2,"%c",ram[i]);
				}
				kbhit();
				if (ram[i] == 0x0A || ram[i] == 0x0C || ram[i] == 0x0D || ram[i] == 0x1D) {
					enter++;
					if (enter > 14) {
						printf("\033[2;16H");
						kbhit();
						enter = 0;
					}
					ch = 0;
				}
				else if (ram[i] == 0x08) {
					ch--;
					if (ch > 0) {
						kbhit();
					}
					else {
						if (enter > 0) {
							printf("\n\033[2A\033[74C");
							kbhit();
							ch = 58;
							enter--;
						}
						else {
							printf("\033[2;16H");
							kbhit();
							ch = 0;
						}
					}
				}
				else if (ram[i] == 0x09) {
					if (ch == 0) {
						ch++;
					}
					else {
						ch += 8;
					}
					if (ch > 58) {
						ch = 0;
						if (enter > 14) {
							printf("\033[2;16H");
							kbhit();
							enter = 0;
						}
						else {
							printf("\n\033[15C");
							kbhit();
							enter++;
						}
					}
				}
				else if (ram[i] == 0x0B) {
					enter++;
					if (enter > 14) {
						printf("\033[15A");
						kbhit();
						enter = 0;
					}
				}
				else {
					if (ram[i] < 0x08 || ram[i] == 0x7F || ( ram[i] > 0x0E && ram[i] < 0x1F)) {
						kbhit();
					}
					else {
						ch++;
					}
					if (ch > 58) {
						ch = 0;
						if (enter > 14) {
							printf("\033[2;16H");
							kbhit();
							enter = 0;
						}
						else {
							printf("\n\033[15C");
							kbhit();
							enter++;
						}
					}
				}
				break;
			case 0x2C:
				ram[i] = input();
				wh++;
				break;
			case 0x3C:
				if (i == 0) {
					i = 499;
				}
				else {
					i--;
				}
				wh++;
				miss(ram,i);
				break;
			case 0x3E:
				if (i == 499) {
					i = 0;
				}
				else {
					i++;
				}
				wh++;
				miss(ram,i);
				break;
			case 0x2D:
				if (ram[i] == 0) {
					ram[i] = 259;
				}
				else {
					ram[i]--;
				}
				wh++;
				miss(ram,i);
				break;
			case 0x2B:
				if (ram[i] == 259) {
					ram[i] = 0;
				}
				else {
					ram[i]++;
				}
				wh++;
				miss(ram,i);
				break;
			default:
				break;
		}
		if (kbhit_if() == 1) {
			getchar();
			Clear
			fclose(fp2);
			fclose(fp);
			return;
		}
	}
	Clear
	fclose(fp);
	if (fp2) {
		fclose(fp2);
	}
	printf("\033[1;31m\n\033[16C程序结束\n\033[16C按下任意键继续\033[0m");
	input();
	return;
}

