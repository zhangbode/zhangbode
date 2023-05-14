#ifndef __TUIXIANGZI_H__
#define __TUIXIANGZI_H__

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define ROW 12   //地图行数
#define COL 12   //地图列数
#define NUM 5   //地图总数
enum MENU
{
	EXIT,
	PLAY
};

struct MAP
{
	const int row;
	const int col;
	char map[ROW][COL];
};

void menu();  //菜单

void game();  //游戏实现函数

void print_map(char (*map)[COL], const int *row, const int *col);  //打印地图

void find_man(char (*map)[COL], const int *row, const int *col, int *x, int *y);  //找到玩家的坐标

void player_act(char (*map)[COL], int *x, int *y);  //玩家控制小人行动

int is_win(char (*map)[COL], const int *row, const int *col);    //判断是否胜利

#endif  //__TUIXIANGZI_H__