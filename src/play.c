#include "../include/head.h"

#define LOCK pthread_mutex_lock(&MUTEX)
#define UNLOCK pthread_mutex_unlock(&MUTEX)

static void printBoard();

pthread_mutex_t MUTEX;

int farme = 0;
int flag_exit = 1;

int play()
{
	pthread_t pid;
	states = 1;

	flag_exit = 1;
	pthread_create(&pid, NULL, running, NULL);
	while (input != 'q' && input != 'Q' && input != 0x1B && input != '0') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		clear();
		printBoard();
		input = 0;
		if (kbhit())
			input = _getch();
		usleep(cfg[4]*TPS);
		farme++;
		input = (input >= 'a' && input <= 'z') ? input - 32 : input;
		if (input == 0x1B && kbhit()) {
			int table[256] = {['A'] = 'W', ['B'] = 'S', ['C'] = 'D', ['D'] = 'A'};
			getchar();
			input = getchar();
			input = table[input];
		}
		switch (input) {
		case 'W':	/* 上 */
		case 'K':
			if (y <= 1) {
				y = MaxY;
			} else {
				y--;
			}
			break;
		case 'S':	/* 下 */
		case 'J':
			if (y >= MaxY) {
				y = 1;
			} else {
				y++;
			}
			break;
		case 'D':	/* 右 */
		case 'L':
			if (x >= MaxX) {
				x = 1;
			} else {
				x++;
			}
			break;
		case 'A':	/* 左 */
		case 'H':
			if (x <= 1) {
				x = MaxX;
			} else {
				x--;
			}
			break;
		case 'G':	/* 切换状态：1关 2开（3单步 4上锁，对象操作中） */
		case 'P':
			if (states == 1 || states == 2) {
				states = 3 - states;
			}
			break;
		case 'N':	/* 单步调用,单步执行完毕自动回到关闭状态 */
			states = 3;
			break;
		case 'R':	/* 重置整个棋盘 */
			for (int i = 0; i < 200; i++) {
				for (int i2 = 0; i2 < 200; i2++) {
					board[i][i2] = 1;
				}
			}
			break;
		case 'C':	/* 清屏，可用作恢复正常显示使用 */
			clear();
			printBoard();
			break;
		case ' ':	/* 更改细胞状态 */
		case '\n':	/* 1死 2活 其他为意外/错误值 */
		case '\r':
			board[y - 1][x - 1] = 3 - board[y - 1][x - 1];
			break;
		case '.':	/* 更该对应的值为错误值（设置Wall墙） */
			if (cfg[3]) {
				if (board[y - 1][x - 1]) {
					board[y - 1][x - 1] = 0;
				} else {
					board[y - 1][x - 1] = 1;
				}
			}
			break;
		case 'O':	/* 设置 */
			states = 1;
			flag_exit = 0;
			usleep(TPS);
			settings();
			flag_exit = 1;
			pthread_create(&pid, NULL, running, NULL);
			break;
		case '1':	/* 快速粘贴：滑翔者 */
			if (cfg[0] && y >= 1 && y <= MaxY - 3 && x >= 1
			    && x <= MaxX - 3) {
				int past[3][3] = {	/* 向右下方滑翔 */
					{1, 2, 1,},	/*       #%       */
					{1, 1, 2,},	/*          #%    */
					{2, 2, 2,}	/*    #% #% #%    */
				};
				int states2 = states;
				states = 4;
				input = getch();
				for (int i = 0; i < 3 && input == 'l'; i++) {	/* 朝右下 */
					for (int i2 = 0; i2 < 3; i2++) {
						board[y + i - 1][x + i2 - 1] =
						    past[i][i2];
					}
				}
				for (int i = 0; i < 3 && input == 'h'; i++) {	/* 朝左下 */
					for (int i2 = 2; i2 >= 0; i2--) {
						board[y + i - 1][x + 2 - i2 -
								 1] =
						    past[i][i2];
					}
				}
				for (int i = 2; i >= 0 && input == 'j'; i--) {	/* 朝左上 */
					for (int i2 = 2; i2 >= 0; i2--) {
						board[y + 2 - i - 1][x + 2 -
								     i2 - 1] =
						    past[i2][i];
					}
				}
				for (int i = 2; i >= 0 && input == 'k'; i--) {	/* 朝右上 */
					for (int i2 = 0; i2 < 3; i2++) {
						board[y + 2 - i - 1][x + i2 -
								     1] =
						    past[i2][i];
					}
				}
				printBoard();
				states = states2;
			}
			break;
		case '2':	/* 快速粘贴：轻型宇宙飞船 */
			if (cfg[0] && y >= 1 && y <= MaxY - 5 && x >= 1
			    && x <= MaxX - 5) {
				int past[4][5] = {	/* 飞船头朝右 */
					{2, 1, 1, 2, 1,},	/*    #%       #%       */
					{1, 1, 1, 1, 2,},	/*                #%    */
					{2, 1, 1, 1, 2,},	/*    #%          #%    */
					{1, 2, 2, 2, 2,}	/*       #% #% #% #%    */
				};
				int states2 = states;
				states = 4;
				input = getch();
				for (int i = 0; i < 4 && input == 'l'; i++) {	/* 朝右 */
					for (int i2 = 0; i2 < 5; i2++) {
						board[y + i - 1][x + i2 - 1] =
						    past[i][i2];
					}
				}
				for (int i = 0; i < 4 && input == 'h'; i++) {	/* 朝左 */
					for (int i2 = 4; i2 >= 0; i2--) {
						board[y + i - 1][x + 4 - i2 -
								 1] =
						    past[i][i2];
					}
				}
				for (int i = 0; i < 5 && input == 'j'; i++) {	/* 朝下 */
					for (int i2 = 0; i2 < 4; i2++) {
						board[y + i - 1][x + i2 - 1] =
						    past[i2][i];
					}
				}
				for (int i = 4; i >= 0 && input == 'k'; i--) {	/* 朝上 */
					for (int i2 = 3; i2 >= 0; i2--) {
						board[y + 4 - i - 1][x + 3 -
								     i2 - 1] =
						    past[i2][i];
					}
				}
				printBoard();
				states = states2;
			}
			break;
		case '3':	/* 快速粘贴：轻型宇宙飞船 */
			if (cfg[0] && y >= 1 && y <= MaxY - 36 && x >= 1
			    && x <= MaxX - 36) {
				int past[9][36] = {	/* 飞船头朝右 */
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},	/*    #%    */
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1},	/*    #%    */
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 2},	/*    #%    */
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 2},	/*    #%    */
					{2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1},	/*    #%    */
					{2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1},	/*    #%    */
					{1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},	/*    #%    */
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},	/*    #%    */
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},	/*    #%    */
				};
				int states2 = states;
				states = 4;
				input = getch();
				for (int i = 0; i < 9 && input == 'l'; i++) {	/* 朝右 */
					for (int i2 = 0; i2 < 36; i2++) {
						board[y + i - 1][x + i2 - 1] =
						    past[i][i2];
					}
				}
				for (int i = 0; i < 9 && input == 'h'; i++) {	/* 朝左 */
					for (int i2 = 35; i2 >= 0; i2--) {
						board[y + i - 1][x + 35 - i2 -
								 1] =
						    past[i][i2];
					}
				}
				for (int i = 35; i >= 0 && input == 'j'; i--) {	/* 朝下 */
					for (int i2 = 8; i2 >= 0; i2--) {
						board[y + 35 - i - 1][x + 8 -
								      i2 - 1] =
						    past[i2][i];
					}
				}
				for (int i = 35; i >= 0 && input == 'k'; i--) {	/* 朝上 */
					for (int i2 = 0; i2 < 9; i2++) {
						board[y + 35 - i - 1][x + i2 -
								      1] =
						    past[i2][i];
					}
				}
				printBoard();
				states = states2;
			}
			break;
		}
	}
	alarm(0);
	flag_exit = 0;
	return 0;
}

void _running()
{
	char board2[1024][1024];
	int count = 0;

	LOCK;
	/*clear();*/
	/*printBoard();*/
	if (states == 1 || states == 4) {
		UNLOCK;
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
					if (i + i3 >= 0 && i + i3 < MaxY
					    && i2 + i4 >= 0 && i2 + i4 < MaxX
					    && board[i + i3][i2 + i4] == 2) {
						count++;
					}
				}
			}
			if (board[i][i2] == 2) {
				count--;
			}
			if (board[i][i2] == 1 && count == 3) {	/* 复活 */
				board2[i][i2] = 3 - board2[i][i2];
			}
			//  else if (board[i][i2] == 2 && (count == 2 || count == 3)) {    /* 保持不变 */
			//  }
			else if (board[i][i2] == 2 && (count >= 4 || count <= 1)) {	/* 死亡 */
				board2[i][i2] = 3 - board2[i][i2];
			}
		}
	}
	for (int i = 0; i < MaxY; i++) {
		for (int i2 = 0; i2 < MaxX; i2++) {
			board[i][i2] = board2[i][i2];
		}
	}
	/*printBoard();*/
	if (states == 3) {
		states = 1;
	}
	UNLOCK;
}

void *running() {
	while ( flag_exit ) {
		_running();
		usleep(daley);
	}
	return NULL;
}

static void printBoard()
{
	int i = 0;
	attron(COLOR_PAIR(1));
	for (int i = 0; i < LINES; i++) {
		for (int i2 = 0; i2 < COLS; i2++) {
			mvaddch(i, i2, ' ');
		}
	}
	attroff(COLOR_PAIR(1));
	if (!cfg[2]) {
		attron(COLOR_PAIR(6));
	} else {
		attron(COLOR_PAIR(1));
	}
	for (i = 0; i < MaxY; i++) {
		for (int i2 = 0; i2 < MaxX; i2++) {
			if (!cfg[2]) {
				if (board[i][i2] == 2) {
					mvaddstr(i, (i2 + 1) * 2 - 2, "  ");
				} else if (board[i][i2] != 1) {
					mvaddstr(i, (i2 + 1) * 2 - 2, "##");
				}
			} else {
				if (board[i][i2] == 2) {
					attroff(COLOR_PAIR(1));
					attron(COLOR_PAIR(6));
					move(i, (i2 + 1) * 2 - 2);
					printw("%2d", board[i][i2]);
					attroff(COLOR_PAIR(6));
					attron(COLOR_PAIR(1));
				} else {
					if (board[i][i2] < 0
					    || board[i][i2] > 9) {
						move(i, (i2 + 1) * 2 - 2);
						printw("%2d", board[i][i2]);
					} else {
						move(i, (i2 + 1) * 2 - 2);
						printw("%2d", board[i][i2]);

					}
				}
			}
		}
	}
	if (!cfg[2]) {
		attroff(COLOR_PAIR(6));
	} else {
		attroff(COLOR_PAIR(1));
	}
	attron(COLOR_PAIR(9));
	attron(A_BOLD);
	mvaddstr(LINES - 1, 0, "运行状态(Run States)：");
	attroff(COLOR_PAIR(9));

	if (states > 0 && states < 5) {
		attron(COLOR_PAIR(6+states));
		char *tag[4] = {"暂停", "运行", "分步运行", "粘贴预设"};
		printw("%s", tag[states - 1]);
		attroff(COLOR_PAIR(6+states));
	}

	attron(COLOR_PAIR(9));
	if (cfg[1]) {
		printw("  输入字符(input char)：");
		attroff(COLOR_PAIR(9));
		attron(COLOR_PAIR(8));
		printw("%2c", input);
		attroff(COLOR_PAIR(8));
		attron(COLOR_PAIR(9));
		printw("  X：");
		attroff(COLOR_PAIR(9));
		attron(COLOR_PAIR(8));
		printw("%3d", x);
		attroff(COLOR_PAIR(8));
		attron(COLOR_PAIR(9));
		printw("  Y：");
		attroff(COLOR_PAIR(9));
		attron(COLOR_PAIR(8));
		printw("%3d", y);
		attroff(COLOR_PAIR(8));
		printw("  farme:%3d", farme);
	}
	move(y - 1, x * 2 - 2);
	if (board[y - 1][x - 1] != 1) {
		attron(COLOR_PAIR(6));
		printw("><");
		attroff(COLOR_PAIR(6));
	} else {
		attron(COLOR_PAIR(1));
		printw("><");
		attroff(COLOR_PAIR(1));
	}
	attroff(A_BOLD);
	refresh();
	return;
}

