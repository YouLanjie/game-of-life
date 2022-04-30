#include "../include/head.h"

void * running() {
	int count = 0;
	char board2[Max][Max];

	for (int i = 0; i < Max; i++) {
		for (int i2 = 0; i2 < Max; i2++) {
			board2[i][i2] = 1;
		}
	}
	while (1) {
		if (states != 1) {
			for (int i = 1; i < Max - 2; i++) {
				for (int i2 = 1; i2 < Max - 2; i2++) {
					if (board[i - 1][i2 - 1] == 2) {
						count++;
					}
					if (board[i - 1][i2] == 2) {
						count++;
					}
					if (board[i - 1][i2 + 1] == 2) {
						count++;
					}
					if (board[i][i2 - 1] == 2) {
						count++;
					}
					if (board[i][i2 + 1] == 2) {
						count++;
					}
					if (board[i + 1][i2 - 1] == 2) {
						count++;
					}
					if (board[i + 1][i2] == 2) {
						count++;
					}
					if (board[i + 1][i2 + 1] == 2) {
						count++;
					}
					if (board[i][i2] == 1 && count == 3) {
						board2[i][i2] = 2;
					}
					else if (board[i][i2] == 2 && count < 2) {
						board2[i][i2] = 2;
					}
					else if (board[i][i2] == 2 && (count == 2 || count == 3)) {
						board2[i][i2] = 2;
					}
					else if (board[i][i2] == 2 && count > 2) {
						board2[i][i2] = 1;
					}
				}
			}
			for (int i = 0; i < Max; i++) {
				for (int i2 = 0; i2 < Max; i2++) {
					board[i][i2] = board2[i][i2];
				}
			}
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
				printf("\n\r");
			}
			printf("运行状态：%d\033[%d;%dH\033[1;32m>\033[0m", states, y, (x - 1) * 2 + 1);
			sleep(1);
		}
	}
	pthread_exit(0);
}

