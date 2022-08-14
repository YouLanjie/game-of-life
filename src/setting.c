#include "../include/head.h"

void settings() {
	menuData data;

	menuDataInit(&data);
	data.title = "设置";
	data.cfg   = 3;
	data.addText(&data, "秒数", "微秒数", "快速粘贴", " ", "调试选项", "显示调试信息", "显示细胞状态值", "更多按键", NULL);
	data.addTextData(&data, 0, "%s %s %s N %s %s %s %s", "%z设置游戏更新间隔的秒数%z", "%z设置游戏更新间隔的微秒数%z", "%z快速粘贴一些游戏内内置的装置%z", "%z开启调试或说是测试功能%z", "%z显示更多（调试）信息%z", "%z显示游戏细胞的真实数字%z", "%z开启更多的编辑按键%z");
	data.addTextData(&data, 1, "%s %s %s N N  %s %s %s", 1, 1, 2, 2, 2, 2);
	data.addTextData(&data, 2, "%s %s %s N N  %s %s %s", &tick.it_interval.tv_sec, &tick.it_interval.tv_usec, &cfg[0], &cfg[1], &cfg[2], &cfg[3]);
	data.addTextData(&data, 3, "%s %s", 1, 5000);

	data.menuShow(&data);
	return;
}

