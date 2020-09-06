#include <iostream>
#include <Windows.h>

typedef COORD Position;

// go_to_xy()
// ... 커서의 위치를 지정된 (x, y)로 바꾼다.
//
void go_to_xy(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// putchar_at_xy()
// ... (x, y)로 커서를 옮긴 후 문자를 찍는다.
//
void putchar_at_xy(int x, int y, char ch)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	putchar(ch);
}