#include <iostream>
#include <Windows.h>

typedef COORD Position;

// go_to_xy()
// ... Ŀ���� ��ġ�� ������ (x, y)�� �ٲ۴�.
//
void go_to_xy(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// putchar_at_xy()
// ... (x, y)�� Ŀ���� �ű� �� ���ڸ� ��´�.
//
void putchar_at_xy(int x, int y, char ch)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	putchar(ch);
}