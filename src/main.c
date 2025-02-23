#include "../include/head.h"

short int states = 1;
char board[1024][1024];
short int x = 1, y = 1;
struct winsize size;		/* 记录窗口大小 */

int daley = 30000;
int input = '1';
int cfg[] = { 1, 0, 0, 0, 1 , 5000};

int main()
{
	cmenu data = cmenu_create();

	ctools_ncurses_init();

	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	cmenu_set_title(data, "生命游戏");
	cmenu_add_text(data, 0, "1.开始游戏", NULL, NULL, NULL, NULL, 0, 0, 0);
	cmenu_add_text(data, 0, "2.游戏设置", NULL, NULL, NULL, NULL, 0, 0, 0);
	cmenu_add_text(data, 0, "3.游戏帮助", NULL, NULL, NULL, NULL, 0, 0, 0);
	cmenu_add_text(data, 0, "4.退出游戏", NULL, NULL, NULL, NULL, 0, 0, 0);

	init_pair(6, COLOR_WHITE, COLOR_RED);
	init_pair(7, COLOR_RED, COLOR_BLUE);
	init_pair(8, COLOR_GREEN, COLOR_BLUE);
	init_pair(9, COLOR_YELLOW, COLOR_BLUE);
	init_pair(10, COLOR_BLUE, COLOR_BLUE);

	/*signal(SIGALRM, running);*/
	initscr();
	cbreak();
	noecho();
	for (int i = 0; i < 200; i++) {
		for (int i2 = 0; i2 < 200; i2++) {
			board[i][i2] = 1;
		}
	}
	while (input != '0') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		input = cmenu_show(data);
		switch (input) {
		case 1:
			play();
			break;
		case 2:
		case 'o':
		case 'O':
			settings();
			break;
		case 3:
			help();
			break;
		case 0:
		case 4:
			endwin();
			return 0;
			break;
		}
	}
	endwin();
	return 0;
}
