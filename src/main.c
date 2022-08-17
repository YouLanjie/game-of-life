#include "../include/head.h"

short int states = 1;
char board[1024][1024];
short int x = 1, y = 1;
struct winsize size;    /* 记录窗口大小 */

struct itimerval tick;
int input = '1';
int cfg[] = {1, 0, 0, 0};

int main(/*int argc, char * argv[]*/) {
	menuData data = menuDataInit();

	data.title = "生命游戏";
	data.addText(&data, "1.开始游戏", "2.游戏设置", "3.游戏帮助", "4.退出游戏", NULL);

	/* 定时间隔 */
	tick.it_interval.tv_sec = 0;
	tick.it_interval.tv_usec = 150000;
	/* 延迟启动 */
	tick.it_value.tv_sec = 0;
	tick.it_value.tv_usec = 50000;

	signal(SIGALRM, running);
	for (int i = 0; i < 200; i++) {
		for (int i2 = 0; i2 < 200; i2++) {
			board[i][i2] = 1;
		}
	}
	printf("\033[?25l");
	while(input != '0') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		input = data.menuShow(&data);
		switch(input) {
			case '1':
				play();
				break;
			case '2':
			case 'o':
			case 'O':
				settings();
				break;
			case '3':
				help();
				break;
			case '0':
			case '4':
				printf("\033[?25h");
				return 0;
				break;
		}
	}
	printf("\033[?25h");
	return 0;
}

