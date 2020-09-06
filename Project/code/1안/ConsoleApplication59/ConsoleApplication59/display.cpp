#include <iostream>
#include <cstdlib>
#include "display.h"
#include <time.h>
#include "snake_game.h"

using namespace std;

// ������()
//
Display::Display() : max_x_(79), max_y_(24) {}

// max_x()
//
const int Display::max_x() const
{
	return max_x_;
}

// max_y()
//
const int Display::max_y() const
{
	return max_y_;
}

// print_prompt()
// ... �־��� �޼����� ȭ���� �߾ӿ� ����Ѵ�.
//
void Display::print_prompt(const char *msg)
{
	go_to_xy(0, 10);
	for (int i = 0; i < 80; i++)
		printf("-");

	go_to_xy(0, 12);
	for (int i = 0; i < 80; i++)
		printf("-");

	go_to_xy(40 - strlen(msg) / 2, 11);
	printf("%s", msg);
}

// print_wall()
// ... ���� ��� �� ���� ������ ���� ����Ѵ�.
//
void Display::print_wall()
{
	// ����ȭ���� �� �������� ����Ѵ�.
	putchar_at_xy(0, 0, '=');
	putchar_at_xy(max_x(), 0, '=');
	putchar_at_xy(0, max_y(), '=');
	putchar_at_xy(max_x(), max_y(), '=');

	// ��� �������� ����Ѵ�.
	for (int x = 1, y = 0; x < max_x(); x++)
		putchar_at_xy(x, y, '=');

	// �ϴ� �������� ����Ѵ�.
	for (int x = 1, y = max_y(); x < max_x(); x++)
		putchar_at_xy(x, y, '=');

	// ���� �������� ����Ѵ�.
	for (int x = 0, y = 1; y < max_y(); y++)
		putchar_at_xy(x, y, '=');

	// ���� �������� ����Ѵ�.
	for (int x = max_x(), y = 1; y < max_y(); y++)
		putchar_at_xy(x, y, '=');
}

// print_food()
// ... �Է¹��� ��ġ�� ���� ���̸� ����Ѵ�.
//
void Display::print_food(Position pos)
{
	putchar_at_xy(pos.X, pos.Y, 'c');
}

void Display::print_food_a(Position posa)
{
	putchar_at_xy(posa.X, posa.Y, 'a');
}

void Display::print_food_b(Position posb)
{
	putchar_at_xy(posb.X, posb.Y, 'b');
}

void Display::print_snake(Snake snake)
{
	list<Position>::const_iterator iter = snake.body().begin();

	// ���� �Ӹ��� ����Ѵ�.
	putchar_at_xy(iter->X, iter->Y, 'o');

	// ���� ������ ����Ѵ�.
	while (++iter != snake.body().end())
		putchar_at_xy(iter->X, iter->Y, 'o');

}

void Display::clear()
{
	system("cls");
}