#include "util.h"

void gotoxy(int x, int y) //�ú��������ù�굽��������
{
	COORD p = { x,y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, p);
}

void getxy(int* x, int* y) //�ú�����ȡ��ǰ����̨���λ��
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &c);
	*x = c.dwCursorPosition.X;
	*y = c.dwCursorPosition.Y;
}