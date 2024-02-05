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
	const struct ctools_menu m = ctools_init().menu;
	struct ctools_menu_t * data = NULL;

	m.data_init(&data);
	m.set_title(data, "游戏设置");
	m.set_type(data, "setting");
	m.set_text(data, "存储输入和输出", NULL);
	m.set_text_data(data, "describe", "%s", "在本地存储数据目录");
	m.set_text_data(data, "type", "%s", "button");
	m.set_text_data(data, "var", "%s", &flag_file);
	m.show(data);
}

