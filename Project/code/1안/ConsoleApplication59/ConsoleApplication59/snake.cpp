#include "snake.h"

// ������()
//
Snake::Snake()
{
	initialize();
}

// head()
// ... �� �Ӹ��� ��ġ�� ��ȯ�Ѵ�.
//
const Position Snake::head() const
{
	return body_.front();
}

// tail()
// ... �� ���� �� �� ��ġ�� ��ȯ�Ѵ�.
//
const Position Snake::tail() const
{
	return body_.back();
}

// body()
// ... �� ��ü�� ��ġ�� ����ִ� list�� ��ȯ�Ѵ�.
//
list<Position>& Snake::body()
{
	return body_;
}

// body()
// ... �� ��ü�� ��ġ�� ����ִ� list�� �����ü�� ��ȯ�Ѵ�.
//
const list<Position> Snake::body() const
{
	return body_;
}

// initialize()
// ... �� ��ü ������ �ʱ�ȭ�Ѵ�.
//
void Snake::initialize()
{
	body_.clear();

	Position pos[2] = { { 40, 12 },{ 40, 13 } };
	body_.push_front(pos[0]);
	body_.push_back(pos[1]);

	direction_ = UP;
}

// set_direction()
// ... ���� �����̴� ������ �����Ѵ�.
//
void Snake::set_direction(Keyboard key)
{
	// ���� ������⿡�� ���ݴ�������δ� ������ȯ�� �Ҽ� ����.
	if (direction_ == UP && key == DOWN) return;
	if (direction_ == DOWN && key == UP) return;
	if (direction_ == LEFT && key == RIGHT) return;
	if (direction_ == RIGHT && key == LEFT) return;

	direction_ = key;
}

// move()
// ... ������ �Ӹ��� �������� �ٲپ� ����ϰ�
// ... ������⿡ ���� �˸´� move�Լ��� ȣ���Ѵ�.
//


void Snake::move()
{
	putchar_at_xy(head().X, head().Y, 'o');

	switch (direction_)
	{
	case UP:    move_up();    break;
	case DOWN:  move_down();  break;
	case LEFT:  move_left();  break;
	case RIGHT: move_right(); break;
	}
}

// move_up()
//
void Snake::move_up()
{
	Position new_head = { head().X, head().Y - 1 };
	body_.push_front(new_head);
}

// move_down()
//
void Snake::move_down()
{
	Position new_head = { head().X, head().Y + 1 };
	body_.push_front(new_head);
}

// move_left()
//
void Snake::move_left()
{
	Position new_head = { head().X - 1, head().Y };
	body_.push_front(new_head);
}

// move_right()
//
void Snake::move_right()
{
	Position new_head = { head().X + 1, head().Y };
	body_.push_front(new_head);
}

// is_bitten()
// ... ���� �ڱ� ���� �������� true, �ƴϸ� false�� ��ȯ�Ѵ�.
//
bool Snake::is_bitten()
{
	list<Position>::const_iterator iter = body_.begin();
	while (++iter != body_.end())
		if ((iter->X == head().X) && (iter->Y == head().Y))
			return true;

	return false;
}