#include "tools.h"                         //头文件

#define MaxX (size.ws_col-1)/4*2      /* x轴 */
#define MaxY size.ws_row-1            /* y轴 */

#define SECOND 1000000
#define TPS (SECOND / 20)

int play();
void *running();
void help();
void settings();

extern char board[1024][1024];
extern short int states;
extern short int x, y;
extern int input;
extern int cfg[];

extern struct winsize size;    /* 记录窗口大小 */

extern int daley;

