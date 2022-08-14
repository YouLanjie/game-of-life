#include "../include/head.h"

static void printBoard();

static int Lock  = 0;

int play() {
	alarm(0);
	states = 1;

	if (setitimer(ITIMER_REAL, &tick, NULL)) {
		perror("Error");
		getchar();
		return -1;
	}
	while (input != 'q' && input != 'Q' && input != 0x1B && input != '0') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		while (Lock);
		printBoard();
		input = getch();
		switch (input) {
			case 0x1B:
				if (kbhit() != 0) {
					getchar();
					input = getch();
					switch (input) {
						case 'A':
							if (y <= 1) {
								y = MaxY;
							}
							else {
								y--;
							}
							break;
						case 'B':
							if (y >= MaxY) {
								y = 1;
							}
							else {
								y++;
							}
							break;
						case 'C':
							if (x >= MaxX) {
								x = 1;
							}
							else {
								x++;
							}
							break;
						case 'D':
							if (x <= 1) {
								x = MaxX;
							}
							else {
								x--;
							}
							break;
					}
				}
				break;
			case 'w':    /* 上 */
			case 'W':
			case 'k':
			case 'K':
				if (y <= 1) {
					y = MaxY;
				}
				else {
					y--;
				}
				break;
			case 's':    /* 下 */
			case 'S':
			case 'j':
			case 'J':
				if (y >= MaxY) {
					y = 1;
				}
				else {
					y++;
				}
				break;
			case 'd':    /* 右 */
			case 'D':
			case 'l':
			case 'L':
				if (x >= MaxX) {
					x = 1;
				}
				else {
					x++;
				}
				break;
			case 'a':    /* 左 */
			case 'A':
			case 'h':
			case 'H':
				if (x <= 1) {
					x = MaxX;
				}
				else {
					x--;
				}
				break;
			case 'g':    /* 切换状态：1关 2开（3单步 4上锁，对象操作中） */
			case 'G':
			case 'p':
			case 'P':
				if (states == 1 || states == 2) {
					states = 3 - states;
				}
				break;
			case 'n':    /* 单步调用 */
			case 'N':    /* 单步执行完毕自动回到关闭状态 */
				states = 3;
				break;
			case 'r':    /* 重置整个棋盘 */
			case 'R':
				for (int i = 0; i < 200; i++) {
					for (int i2 = 0; i2 < 200; i2++) {
						board[i][i2] = 1;
					}
				}
				break;
			case 'c':    /* 清屏，可用作恢复正常显示使用 */
			case 'C':
				Clear2
				while (Lock);
				Lock = 1;
				printBoard();
				Lock = 0;
				break;
			case ' ':     /* 更改细胞状态 */
			case '\n':    /* 1死 2活 其他为意外/错误值 */
			case '\r':
				while (Lock);
				board[y - 1][x - 1] = 3 - board[y - 1][x - 1];
				break;
			case '.':    /* 更该对应的值为错误值（设置Wall墙） */
				if (cfg[3]) {
					if (board[y - 1][x - 1]) {
						board[y - 1][x - 1] = 0;
					}
					else {
						board[y - 1][x - 1] = 1;
					}
				}
				break;
			case 'o':    /* 设置 */
			case 'O':
				states = 1;
				alarm(0);
				settings();
				if (setitimer(ITIMER_REAL, &tick, NULL)) {
					perror("Error");
					getch();
					return -1;
				}
				break;
			case '1':    /* 快速粘贴：滑翔者 */
				if (cfg[0] && y >= 1 && y <= MaxY - 3 && x >= 1 && x <= MaxX - 3) {
					int past[3][3] = {     /* 向右下方滑翔 */
						{1, 2, 1,},    /*       #%       */
						{1, 1, 2,},    /*          #%    */
						{2, 2, 2,}     /*    #% #% #%    */
					};
					int states2 = states;
					states = 4;
					input = getch();
					while (Lock);
					Lock = 1;
					for (int i = 0; i < 3 && input == 'l'; i++) {    /* 朝右下 */
						for (int i2 = 0; i2 < 3; i2++) {
							board[y + i - 1][x + i2 - 1] = past[i][i2];
						}
					}
					for (int i = 0; i < 3 && input == 'h'; i++) {    /* 朝左下 */
						for (int i2 = 2; i2 >= 0; i2--) {
							board[y + i - 1][x + 2 - i2 - 1] = past[i][i2];
						}
					}
					for (int i = 2; i >= 0 && input == 'j'; i--) {    /* 朝左上 */
						for (int i2 = 2; i2 >= 0; i2--) {
							board[y + 2 - i - 1][x + 2 - i2 - 1] = past[i2][i];
						}
					}
					for (int i = 2; i >= 0 && input == 'k'; i--) {    /* 朝右上 */
						for (int i2 = 0; i2 < 3; i2++) {
							board[y + 2 - i - 1][x + i2 - 1] = past[i2][i];
						}
					}
					Lock = 1;
					printBoard();
					Lock = 0;
					states = states2;
				}
				break;
			case '2':    /* 快速粘贴：轻型宇宙飞船 */
				if (cfg[0] && y >= 1 && y <= MaxY - 5 && x >= 1 && x <= MaxX - 5) {
					int past[4][5] = {           /* 飞船头朝右 */
						{2, 1, 1, 2, 1,},    /*    #%       #%       */
						{1, 1, 1, 1, 2,},    /*                #%    */
						{2, 1, 1, 1, 2,},    /*    #%          #%    */
						{1, 2, 2, 2, 2,}     /*       #% #% #% #%    */
					};
					int states2 = states;
					states = 4;
					input = getch();
					while (Lock);
					Lock = 1;
					for (int i = 0; i < 4 && input == 'l'; i++) {    /* 朝右 */
						for (int i2 = 0; i2 < 5; i2++) {
							board[y + i - 1][x + i2 - 1] = past[i][i2];
						}
					}
					for (int i = 0; i < 4 && input == 'h'; i++) {    /* 朝左 */
						for (int i2 = 4; i2 >= 0; i2--) {
							board[y + i - 1][x + 4 - i2 - 1] = past[i][i2];
						}
					}
					for (int i = 0; i < 5 && input == 'j'; i++) {    /* 朝下 */
						for (int i2 = 0; i2 < 4; i2++) {
							board[y + i - 1][x + i2 - 1] = past[i2][i];
						}
					}
					for (int i = 4; i >= 0 && input == 'k'; i--) {    /* 朝上 */
						for (int i2 = 3; i2 >= 0; i2--) {
							board[y + 4 - i - 1][x + 3 - i2 - 1] = past[i2][i];
						}
					}
					printBoard();
					Lock = 0;
					states = states2;
				}
				break;
		}
	}
	alarm(0);
	return 0;
}

void running() {
	char board2[1024][1024];
	int count = 0;

	Lock = 1;
	printBoard();
	if (states == 1 || states == 4) {
		Lock = 0;
		return;
	}

	for (int i = 0; i < MaxY; i++) {
		for (int i2 = 0; i2 < MaxX; i2++) {
			board2[i][i2] = board[i][i2];
		}
	}
	for (int i = 0; i < MaxY; i++) {
		for (int i2 = 0; i2 < MaxX; i2++) {
			count = 0;
			for (int i3 = -1; i3 < 2; i3++) {
				for (int i4 = -1; i4 < 2; i4++) {
					if (i + i3 >= 0 && i + i3 < MaxY && i2 + i4 >= 0 && i2 + i4 < MaxX && board[i + i3][i2 + i4] == 2) {
						count++;
					}
				}
			}
			if (board[i][i2] == 2) {
				count--;
			}
			if (board[i][i2] == 1 && count == 3) {    /* 复活 */
				board2[i][i2] = 3 - board2[i][i2];
			}
			//  else if (board[i][i2] == 2 && (count == 2 || count == 3)) {    /* 保持不变 */
			//  }
			else if (board[i][i2] == 2 && (count >= 4 || count <= 1)) {    /* 死亡 */
				board2[i][i2] = 3 - board2[i][i2];
			}
		}
	}
	for (int i = 0; i < MaxY; i++) {
		for (int i2 = 0; i2 < MaxX; i2++) {
			board[i][i2] = board2[i][i2];
		}
	}
	printBoard();
	if (states == 3) {
		states = 1;
	}
	Lock = 0;
}

static void printBoard() {
	int i = 0;
	printf("\033[2;44m");
	Clear
	printf("\033[0;1;41m");
	for (i = 0; i < MaxY; i++) {
		for (int i2 = 0; i2 < MaxX; i2++) {
			if (!cfg[2]) {
				if (board[i][i2] == 2) {
					printf("\033[%d;%dH  ", i + 1, (i2 + 1) * 2 - 1);
				}
				else if (board[i][i2] != 1) {
					printf("\033[%d;%dH##", i + 1, (i2 + 1) * 2 - 1);
				}
			}
			else {
				if (board[i][i2] == 2) {
					printf("\033[%d;%dH\033[0;1;41m%2d", i + 1, (i2 + 1) * 2 - 1, board[i][i2]);
				}
				else {
					if (board[i][i2] < 0 || board[i][i2] > 9) {
						printf("\033[%d;%dH\033[0;2;44m%2d", i + 1, (i2 + 1) * 2 - 1, board[i][i2]);
					}
					else {
						printf("\033[%d;%dH\033[0;2;44m%2d", i + 1, (i2 + 1) * 2 - 1, board[i][i2]);

					}
				}
			}
		}
	}
	printf("\033[%d;1H\033[0;1;33;44m运行状态(Run States)：\033[3%dm%02d", i + 1, states, states);
	if (cfg[1]) {
		printf("  \033[0;1;33;44m输入字符(input char)：\033[32m%2c  \033[0;1;33;44mX：\033[32m%3d  \033[0;1;33;44mY：\033[32m%3d", input, x, y);
	}
	printf("\033[0m\033[%d;%dH", y, x * 2 - 1);
	if (board[y - 1][x - 1] != 1) {
		printf("\033[1;37;41m><\033[0m");
	}
	else {
		printf("\033[1;37;44m><\033[0m");
	}
	kbhitGetchar();
	return;
}

