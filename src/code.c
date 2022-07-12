#include "../include/head.h"

void code(int h,char filename[]) {
	struct InputStruct * pHead = NULL, * pTemp = NULL;      //用于输入的链表结构体

	long w[500];
	int a = 0;
	short status = 0;
	unsigned short i = 0, w1 = 0,q = 1;          /* i用作表示模拟的指针所指的内存序号 */
	unsigned short ram[500];                               //用于存储内存数据
	char wh = 0;

	FILE * fp,* fp2;

	//创建输入缓存
	mkdir("Brain-Fuck", 0744);
	if (h == 0) {
		pHead = pTemp = New();
		fp = fopen(filename, "w");
		if(!fp) {
			perror("\033[1;31m[Code]\033[0m");
			getch();
			return;
		}
		while (pTemp != NULL) {
			fprintf(fp,"%c",pTemp -> m);
			pTemp = pTemp -> pNext;
		}
		free(pHead);
		pHead = NULL;
		fclose(fp);
		Clear2
	}
	//打开文件
	fp = fopen(filename,"rb");
	if (!fp) {
		printf("\033[1;31m错误[Error]: %s: 没有那个文件或目录\a\033[0m\n",filename);
		getch();
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
		getch();
	}
	printf("\033[3;16H");
	kbhitGetchar();
	if (a != EOF) {
		a = fgetc(fp);
		if (a == 0x0D || a == 0x0A) { //即回车与换行键
			status = 1;
		}
		fseek(fp, 0L, 0);
	}
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
			case 0x5B:        //"["循环开始
				if (ram[i] != 0) {
					w[w1] = ftell(fp) - 1L;
					w1++;
					wh = 0;
				}
				else {
					q = 0;
				}
				break;
			case 0x5D:         //"]"循环结束
				q = 1;
				if (w1 == 0) {
					Clear
					printf("\033[1;31m错误[Error]: %s: 循环括号不匹配\a\033[0m\n",filename);
					getch();
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
					getch();
					fclose(fp);
					return;
				}
				break;
			case 0x2E:         //"."显示
				printf("%c",ram[i]);
				if(fp2) {      //将输出记录到文件里面
					fprintf(fp2,"%c",ram[i]);
				}
				kbhitGetchar(); //将缓存区的内容写入到文件里
				miss(ram, i, (int*)&status);
				kbhitGetchar();
				break;
			case 0x2C:           //","输入
				ram[i] = getch();
				wh++;
				miss(ram,i,(int*)&status);
				break;
			case 0x3C:           //"<"左移
				if (i == 0) {
					i = 499;
				}
				else {
					i--;
				}
				wh++;
				miss(ram,i,(int*)&status);
				break;
			case 0x3E:           //">"右移
				if (i == 499) {
					i = 0;
				}
				else {
					i++;
				}
				wh++;
				miss(ram,i,(int*)&status);
				break;
			case 0x2D:           //"-"减
				if (ram[i] == 0) {
					ram[i] = 259;
				}
				else {
					ram[i]--;
				}
				wh++;
				miss(ram,i,(int*)&status);
				break;
			case 0x2B:            //"+"加
				if (ram[i] == 259) {
					ram[i] = 0;
				}
				else {
					ram[i]++;
				}
				wh++;
				miss(ram,i,(int*)&status);
				break;
			default:              //其他跳过
				break;
		}
		if (kbhit() == 1) {
			getchar();
			Clear
			fclose(fp2);
			fclose(fp);
			return;
		}
	}
	if (status == 1) {
		printf("\033[1;31m\n\033[16C程序结束\n\033[16C按下任意键继续\033[0m");
	}
	else {
		printf("\033[1;31m\n程序结束\n按下任意键继续\033[0m\n");
	}
	getch();
	Clear
	fclose(fp);
	if (fp2) {
		fclose(fp2);
	}
	return;
}

