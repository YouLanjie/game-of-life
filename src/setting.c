#include "../include/head.h"

void settings()
{
	struct ctools_menu_t * data = NULL;

	CT_MENU.data_init(&data);
	CT_MENU.set_title(data, "设置");
	CT_MENU.set_type(data, "setting");
	CT_MENU.set_text(data, "秒数", "微秒数", "快速粘贴", " ",
		     "调试选项", "显示调试信息",
		     "显示细胞状态值", "更多按键", NULL);
	CT_MENU.set_text_data(data, "describe", "%s %s %s N %s %s %s %s",
			 "设置游戏更新间隔的秒数",
			 "设置游戏更新间隔的微秒数",
			 "快速粘贴一些游戏内内置的装置",
			 "开启调试或说是测试功能",
			 "显示更多（调试）信息",
			 "显示游戏细胞的真实数字",
			 "开启更多的编辑按键");
	CT_MENU.set_text_data(data, "type", "%s %s %s N N  %s %s %s", 1, 1, 2, 2, 2, 2);
	CT_MENU.set_text_data(data, "var", "%s %s %s N N  %s %s %s",
			 &tick.it_interval.tv_sec, &tick.it_interval.tv_usec,
			 &cfg[0], &cfg[1], &cfg[2], &cfg[3]);
	CT_MENU.set_text_data(data, "foot", "%s %s", 1, 5000);

	CT_MENU.show(data);
	return;
}
