#include "headfile/head.h"

int main(int argc,char * argv[]) {
	int i = 0;
	int m = 1;

	if (argc != 1) {
		for (int count = 1; count < argc; count++) {
			Clear
			code(1,argv[count]);
		}
		return 0;
	}
	Clear2
	//printf("\033[?25l");
	while (i != 0x30) {
		welcome(m);
		m = 1;
		i = input();
		printf("\n");
		Clear2
		switch (i) {
			case 0x30:
			case 0x51:
			case 0x71:
				printf("\033[?25h\n");
				Clear2
				return 0;
				break;
			case 0x1B:
				if (kbhit_if() == 1) {
					getchar();
					i = getchar();
					if (i == 0x41 || i == 0x44) {
						if (m > 1) {
							m--;
						}
						else {
							printf("\a");
						}
					}
					else if (i == 0x42 || i == 0x43) {
						if (m < 2) {
							m++;
						}
						else {
							printf("\a");
						}
					}
				}
				else {
					printf("\033[?25h");
					Clear2
					return 0;
					break;
				}
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
				remove("./output.txt");
				rmdir("./Brain-Fuck");
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

void welcome(int m) {
	menu("首页");
	printf("\033[1;33m");
	if (m == 1) {
		printf("\033[8;11H0.退出程序\033[8;37H1.执行代码");
		printf("\033[9;11H2.执行上一次\033[9;37H3.程序帮助");
	}
	else if (m == 2) {
		printf("\033[8;11H4.执行外部文件\033[8;37H9.删除临时文件");
	}
	printf("\033[2;32m\033[6;26H↑\033[10;26H↓\033[0m");
	printf("\033[11;52H\033[2;32m%d/2\033[1;33m",m);
	Menu
	return;
}

void code(int h,char filename[]) {
	int a = 0;
	unsigned short i = 0;
	long w[500];
	unsigned short w1 = 0,q = 1,enter = 0;
	short ch = 0;
	unsigned short ram[500];
	char wh = 0;
	FILE * fp,* fp2;

	if (h == 0) {
		in();
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
	fp2 = fopen("./output.txt","wb");
	if (!fp2) {
		printf("\033[1;31m错误[Error]: 当前目录无法创建文件\a\033[0m\n");
		input();
		return;
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
			case EOF:
				printf("\033[1;31m\n\033[16C程序结束\n\033[16C按下任意键继续\033[0m");
				input();
				break;
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
				fprintf(fp2,"%c",ram[i]);
				kbhit();
				if (ram[i] == 0x0A || ram[i] == 0x0C || ram[i] == 0x0D) {
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
					if (ram[i] < 0x08) {
						kbhit();
					}
					else if (ram[i] == 0x7F) {
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
	fclose(fp2);
	fclose(fp);
	return;
}

void help() {
	char a = 0x00;
	char b = 1;

	while (a == 0x00) {
		Clear2
		menu2("帮助");
		printf("\033[2;32m\033[6;26H↑\033[10;26H↓\033[0m");
		printf("\033[1;33m");
		printf("");
		if (b == 1) {
			printf("\033[7;5H1.↑上翻，↓下翻");
			printf("\033[8;5H2.输入代码时按下Esc退出");
			printf("\033[9;5H3.存储条只有500个");
		}
		else if (b == 2) {
			printf("\033[7;5H4.历史功能直接读取文件信息，不用再次输入");
			printf("\033[8;5H5.主界面按下9删除文件");
			printf("\033[9;5H6.可以执行其他文件，格式\"brain-fuck filename\"");
		}
		else if (b == 3) {
			printf("\033[7;5H7.执行程序时按下任意按键退出");
			printf("\033[8;5H8.执行程序时同时会保存输出");
			printf("\033[9;5H9.不要将窗口缩小到比程序界面还要小");
		}
		printf("\033[11;52H\033[2;32m%d/3\033[1;33m",b);
		Menu2
		a = input();
		if (a == 0x1B) {
			if (kbhit_if() == 1) {
				getchar();
				a = getchar();
				if (a == 0x41 || a == 0x44) {
					if (b > 1) {
						b--;
					}
					else {
						printf("\a");
					}
				}
				else if (a == 0x42 || a == 0x43) {
					if (b < 3) {
						b++;
					}
					else {
						printf("\a");
					}
				}
				a = 0x00;
			}
			else {
				printf("\033[0m");
				Clear
				return;
			}
		}
		Clear
	}
	Clear
	return;
}

void in() {
	int i = 0x00;
	int exit = 1;
	FILE * fp;

	fp = fopen("./Brain-Fuck/input.txt","wb");
	if (!fp) {
		Clear
		mkdir("./Brain-Fuck",0755);
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
				printf("\033[1;9H\033[1;31mError!\033[0m\a");
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

void miss(unsigned short ram[500],unsigned short i) {
	printf("\033[s\033[1;1H");
	kbhit();
	printf("\033[1;1H\033[34m---------------\033[33m--------------------------------------------------------------\033[0m\n");
	for (int count = -7; count < 9; count++) {
		if (i + count >= 0) {
			printf("\033[32m[%3d][%3d]    \033[34m|\033[33m\033[61C|\033[0m\n",i + count + 1,ram[i + count]);
		}
		else {
			printf("\033[32m[NaN][NaN]    \033[34m|\033[33m\033[61C|\033[0m\n");
		}
	}
	printf("\033[34m---------------\033[33m--------------------------------------------------------------\033[0m\n");
	printf("\033[9;12H\033[2;31m<\033[0m\033[H\n");
	printf("\033[u");
	kbhit();
	return;
}
