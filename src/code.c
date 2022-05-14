#include "../include/head.h"

void code(int h,char filename[]) {
	struct InputStruct * pHead = NULL, * pTemp = NULL;      //用于输入的链表结构体

	long w[500];
	int a = 0;
	short status = 0;
	unsigned short i = 0, w1 = 0,q = 1;
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
		if (a == 0x0D) { //即回车键
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
	printf("\033[1;31m\n\033[16C程序结束\n\033[16C按下任意键继续\033[0m");
	getch();
	Clear
	fclose(fp);
	if (fp2) {
		fclose(fp2);
	}
	return;
}

void printbroid(const int status,unsigned short ram[500],unsigned short i) {
	static short ch = 0;
	static unsigned short enter = 0;

	if (status == 1) {
		if (ram[i] == 0x0A || ram[i] == 0x0C || ram[i] == 0x0D || ram[i] == 0x1D) {   //记录回车数值
			enter++;
			if (enter > 14) {
				printf("\033[2;16H");  //移动光标位置（坐标）
				kbhitGetchar();
				enter = 0;
			}
			ch = 0;  //单列字符数清零
		}
		else if (ram[i] == 0x08) {  //退格
			ch--;
			if (ch > 0) {
				kbhitGetchar();
			}
			else {
				if (enter > 0) {
					printf("\n\033[2A\033[74C");
					kbhitGetchar();
					ch = 58;
					enter--;
				}
				else {
					printf("\033[2;16H");
					kbhitGetchar();
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
					kbhitGetchar();
					enter = 0;
				}
				else {
					printf("\n\033[15C");
					kbhitGetchar();
					enter++;
				}
			}
		}
		else if (ram[i] == 0x0B) {
			enter++;
			if (enter > 14) {
				printf("\033[15A");
				kbhitGetchar();
				enter = 0;
			}
		}
		else {
			if (ram[i] < 0x08 || ram[i] == 0x7F || ( ram[i] > 0x0E && ram[i] < 0x1F)) {
				kbhitGetchar();
			}
			else {
				ch++;
			}
			if (ch > 58) {
				ch = 0;
				if (enter > 14) {
					printf("\033[2;16H");
					kbhitGetchar();
					enter = 0;
				}
				else {
					printf("\n\033[15C");
					kbhitGetchar();
					enter++;
				}
			}
		}
	}
	else {
		printf("%c",ram[i]);
		kbhitGetchar();
	}
	return;
}

