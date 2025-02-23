#include "../include/head.h"

void settings()
{
	cmenu data = cmenu_create();

	cmenu_set_title(data, "设置");
	cmenu_set_type(data, "setting");
	/*cmenu_add_text(data, 0, "秒数", "设置游戏更新间隔的秒数", NULL, (int*)&tick.it_interval.tv_sec, "number", 1, 0, 0);*/
	cmenu_add_text(data, 0, "微秒数", "设置游戏更新间隔的微秒数\n1秒等于1000000微秒", NULL, &daley, "number", cfg[5], 1000000000, 0);
	cmenu_add_text(data, 0, "调整步数", "调整微秒的步幅\n重进设置界面生效", NULL, &cfg[5], "number", 10, 0, 0);
	cmenu_add_text(data, 0, "快速粘贴", "快速粘贴一些游戏内内置的装置", NULL, &cfg[0], "button", 0, 0, 0);
	cmenu_add_text(data, 0, "调试选项", "开启调试或说是测试功能", NULL, NULL, "button", 0, 0, 0);
	cmenu_add_text(data, 0, "显示调试信息", "显示更多（调试）信息", NULL, &cfg[1], "button", 0, 0, 0);
	cmenu_add_text(data, 0, "显示细胞状态值", "显示游戏细胞的真实数字", NULL, &cfg[2], "button", 0, 0, 0);
	cmenu_add_text(data, 0, "更多按键", "开启更多的编辑按键", NULL, &cfg[3], "button", 0, 0, 0);
	cmenu_add_text(data, 0, "显示延迟", "", NULL, &cfg[4], "number", 0, 20, 1);
	cmenu_show(data);
	return;
}
