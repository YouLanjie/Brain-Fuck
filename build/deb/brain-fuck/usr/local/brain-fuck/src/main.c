#include "headfile/head.h"
#include <dirent.h>

int main(int argc,char * argv[]) {
	int i = 0;

	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			printf("\033[1;32m%s :\033[0m\n",argv[count]);
			code(1,argv[count]);
		}
		return 0;
	}
	Clear2
	printf("\033[?25l");
	while (i != 0x30) {
		welcome();
		i = input();
		Clear2
		switch (i) {
			case 0x30:
			case 0x1B:
			case 0x51:
			case 0x71:
				printf("\033[?25h");
				Clear2
				return 0;
				break;
			case 0x31:
				code(0,"./Brain-Fuck/input.txt");
				break;
			case 0x32:
				code(1,"./Brain-Fuck/input.txt");
				break;
			case 0x33:
				help();
				break;
			case 0x39:
				remove("./Brain-Fuck/input.txt");
				remove("./Brain-Fuck");
				break;
			default:
				Clear
				break;
		}
		Clear
	}
	printf("\033[?25h");
	Clear2
	return 0;
}

void welcome() {
	menu("首页");
	printf("\033[8;11H\033[1;33m1.执行代码\033[8;37H2.历史");
	printf("\033[9;11H3.帮助");
	Menu
	return;
}

void code(int h,char filename[]) {
	int a = 0;
	unsigned short i = 0;
	long w[500];
	unsigned short w1 = 0,q = 1;
	unsigned short ram[500];
	FILE * fp;

	if (h == 0) {
		in();
		Clear2
	}
	fp = fopen(filename,"rb");
	if (!fp) {
		printf("\033[1;31m错误[Error]: ");
		printf("%s",filename);
		printf(":没有那个文件或者目录\033[0m\n");
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
			case EOF:
				printf("\033[1;31m\n程序结束，按下任意键继续\033[0m\n\n\n");
				input();
				break;
			case 0x5B:
				if (ram[i] != 0) {
					w[w1] = ftell(fp) - 1L;
					w1++;
				}
				else {
					q = 0;
				}
				break;
			case 0x5D:
				q = 1;
				if (w1 == 0) {
					break;
				}
				else {
					w1--;
				}
				fseek(fp,w[w1],0);
				break;
			case 0x2E:
				printf("%c",ram[i]);
				break;
			case 0x3C:
				if (i == 0) {
					i = 499;
				}
				else {
					i--;
				}
				break;
			case 0x3E:
				if (i == 499) {
					i = 0;
				}
				else {
					i++;
				}
				break;
			case 0x2D:
				if (ram[i] == 0) {
					ram[i] = 259;
				}
				else {
					ram[i]--;
				}
				break;
			case 0x2B:
				if (ram[i] == 259) {
					ram[i] = 0;
				}
				else {
					ram[i]++;
				}
				break;
			default:
				break;
		}
	}
	fclose(fp);
	return;
}

void help() {
	menu2("帮助");
	printf("\033[7;11H\033[1;33m1.输入代码时按下Esc退出");
	printf("\033[8;11H2.存储条只有500个");
	printf("\033[9;11H3.历史功能直接读取文件信息，不再输入");
	Menu2
	input();
	return;
}

void in() {
	int i = 0x00;
	int exit = 1;
	FILE * fp;
	DIR * dp;

	fp = fopen("./Brain-Fuck/input.txt","wb");
	if (!fp) {
		Clear
		system("mkdir ./Brain-Fuck");
		fp = fopen("./Brain-Fuck/input.txt","wb");
		if (!fp) {
			return;
		}
	}
	printf("\033[1;1H\033[1;32m请输入：\033[0m\n");
	print();
	do {
		i = input();
		if (i == 0x1B) {
			if (kbhit_if() == 1) {
				getchar();
				i = getchar();
				if (i == 0x44) {
					fseek(fp,-1L,1);
				}
				else if (i == 0x43) {
					fseek(fp,1L,1);
				}
				continue;
			}
			exit = 0;
		}
		else if (i == 0x7F) {
			if (ftell(fp) == 0) {
				printf("\033[1;9H\033[1;31mError!\033[0m\007");
				continue;
			}
			fseek(fp,-1L,1);
			fprintf(fp," ");
			fseek(fp,-1L,1);
			Clear
			printf("\033[1;1H\033[1;32m请输入：\033[0m\n");
			print();
		}
		else {
			fputc(i,fp);                        //此功能靠bug运行，请不要删除它，否则
			fseek(fp,0L,1);                     //无法正常运行
			Clear
			printf("\033[1;1H\033[1;32m请输入：\033[0m\n");
			print();
		}
	} while (exit != 0);
	fclose(fp);
	return;
}

void print() {
	int a = 0;
	FILE * fp;

	fp = fopen("./Brain-Fuck/input.txt","r");
	if (!fp) {
		printf("错误！！！\n");
		return;
	}
	while (a != EOF) {
		a = fgetc(fp);
		if(a == EOF) {
			return;
		}
		else {
			printf("%c",a);
		}
	}
	fclose(fp);
	return;
}
