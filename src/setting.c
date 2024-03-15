/*
 *   Copyright (C) 2024 u0_a221
 *   
 *   文件名称：setting.c
 *   创 建 者：u0_a221
 *   创建日期：2024年02月05日
 *   描    述：
 *
 */

#include "../include/head.h"

void settings()
{
	cmenu data = cmenu_create();

	cmenu_set_title(data, "游戏设置");
	cmenu_set_type(data, "setting");
	cmenu_add_text(data, 0, "存储输入和输出", "在本地存储数据目录", NULL,
		       &flag_file, "button", 0, 0, 0);
	cmenu_show(data);
}

