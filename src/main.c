#include "../include/head.h"

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
	printf("\033[?25l");
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
				remove("./Brain-Fuck/input.txt");
				remove("./Brain-Fuck/output.txt");
				rmdir("./Brain-Fuck");
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
				remove("./Brain-Fuck/output.txt");
				rmdir("./Brain-Fuck");
				break;
			default:
				Clear
				break;
		}
		Clear
	}
	remove("./Brain-Fuck/input.txt");
	remove("./Brain-Fuck/output.txt");
	rmdir("./Brain-Fuck");
	printf("\033[?25h");
	Clear2
	return 0;
}

