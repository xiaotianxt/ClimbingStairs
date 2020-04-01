#include "util.h"

void gotoxy(int x, int y) //该函数可设置光标到任意坐标
{
	COORD p = {x, y};
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, p);
}

void getxy(int *x, int *y) //该函数获取当前控制台光标位置
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &c);
	*x = c.dwCursorPosition.X;
	*y = c.dwCursorPosition.Y;
}