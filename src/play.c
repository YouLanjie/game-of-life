#include "../include/head.h"

int play() {
	int input = 0;
	pthread_t pid;

	for (int i = 0; i < Max; i++) {
		for (int i2 = 0; i2 < Max; i2++) {
			board[i][i2] = 1;
		}
	}
	x = y = states = 1;
	pthread_create(&pid, NULL, running, NULL);
	while (1) {
		Clear2
		printf("\033[H");
		for (int i = 1; i < Max - 2; i++) {
			for (int i2 = 1; i2 < Max - 2; i2++) {
				if (board[i][i2] == 2) {
					printf(" \033[1;31m#\033[0m");
				}
				else {
					printf(" \033[34m+\033[0m");
				}
			}
			printf("\n");
		}
		printf("运行状态：%d\033[%d;%dH\033[1;32m>\033[0m", states, y, (x - 1) * 2 + 1);
		input = getch();
		if (input == '\r' || input == '\n' || input == ' ') {
			board[y][x] = 3 - board[y][x];
		}
		else if (input == 'g' || input == 'G') {
			states = 3 - states;
		}
		else if (input == 'q' || input == 'Q') {
			pthread_cancel(pid);
			return 0;
		}
		else if (input == 0x1B && kbhit() == 1) {
			getchar();
			input = getchar();
			if (input == 'A' && y > 0) {
				y--;
			}
			else if (input == 'B' && y < Max - 2 - 1) {
				y++;
			}
			else if (input == 'D' && x > 0) {
				x--;
			}
			else if (input == 'C' && x < Max - 2 - 1) {
				x++;
			}
		}
	}
	return 0;
}

