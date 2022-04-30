#include "../include/head.h"

short int states = 1;
char board[Max][Max];
short int x = 1, y = 1;

int main(/*int argc, char * argv[]*/) {
	int input = '1';
	char *text[] = {"1.开始游戏","2.退出游戏"};

	//printf("\033[?25l");
	while(input != '0') {
		input = Menu("Game of Life",text,2);
		switch(input) {
			case '1':
			case 1:
				play();
				break;
			case '0':
			case '2':
			case 0:
			case 2:
				printf("\033[?25h");
				return 0;
				break;
		}
	}
	printf("\033[?25h");
	return 0;
}

