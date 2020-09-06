#include <cstdlib>
#include <ctime>
#include <conio.h>
#include<iostream>
#include "snake_game.h"
using namespace std;

// ������()
//
SnakeGame::SnakeGame()
{
	initialize();
}

// initialize()
// ... ���� ��ġ�� ������ �ʱ�ȭ�Ѵ�.
//
void SnakeGame::initialize()
{
	food_position_.X = 0;
	food_position_.Y = 0;
	food_position_a.X = 0;
	food_position_a.Y = 0;
	food_position_b.X = 0;
	food_position_b.Y = 0;

	score_ = 0;
}

// start()
// ... ���� �÷��� �� ���������� ó���Ѵ�.
//
ReturnCode SnakeGame::start()
{
	this->initialize();     // ������ ������ġ�� �ʱ�ȭ�Ѵ�.
	snake_.initialize();    // ���� ���� �� ��ġ�� �ʱ�ȭ�Ѵ�.

	display_.clear();
	display_.print_prompt("Do you want to play? (y/n) ");

	int key;
	do
	{
		key = getch();
	} while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

	switch (key)
	{
	case 'y':
	case 'Y':
		make_food();
		make_food_a();
		make_food_b();
		display_.clear();

		// ȹ���� ������ ����Ѵ�
		go_to_xy(83, 12);
		printf("Your score: %d", score_);

		display_.print_wall();
		display_.print_snake(snake_);
		display_.print_food(food_position_);
		display_.print_food_a(food_position_a);
		display_.print_food_b(food_position_b);
		return RETURN_SUCCESS;
	case 'n':
	case 'N':
		return RETURN_EXIT;
	default:
		return RETURN_UNKNOWN;
	}
}

// play()
// ... ������ ������ �����Ű�� �̺�Ʈ�� ó���Ѵ�.
//
ReturnCode SnakeGame::play()
{
	int key;
	while (FOREVER)
	{
		// Ű���� �Է��� �ִ� ��츦 ó���Ѵ�.
		if (kbhit())
		{
			key = getch();
			if (key == 224)
			{
				// ����Ű�� �ν��� �� ������ �����Ѵ�.
				key = getch();
				switch (key)
				{
				case UP: case DOWN: case LEFT: case RIGHT:
					snake_.set_direction((Keyboard)key);
					break;
				default:
					return RETURN_FATAL;
				}
			}
			else if (key == ESC)
			{
				// �Ͻ����� �� �޴��� ����Ѵ�.
				switch (pause())
				{
				case RETURN_RESUME:
					display_.clear();
		
					go_to_xy(83, 12);
					printf("Your score: %d", score_);

					display_.print_wall();
					display_.print_snake(snake_);
					display_.print_food(food_position_);
					display_.print_food_a(food_position_a);
					display_.print_food_b(food_position_b);
					break;
				case RETURN_NEWGAME:
					return RETURN_NEWGAME;
				case RETURN_STOP:
					return RETURN_SUCCESS;
				case RETURN_EXIT:
					return RETURN_EXIT;
				default:
					return RETURN_UNKNOWN;
				}
			}
		}

		Sleep(GAME_SPEED);

		snake_.move();

		// ���� ���� �ε����� ������ ������.
		if (snake_.head().X == 0 || snake_.head().X == 79 ||
			snake_.head().Y == 0 || snake_.head().Y == 24)
		{
			return RETURN_STOP;
		}

		// ���� �ڱ� ���� �������� ������ ������.
		else if (snake_.is_bitten() == true)
		{
			return RETURN_STOP;
		}

		// ���� ���̸� �Ծ��ٸ� ���� ���̸� �ϳ� ������Ű�� ������ �ø���.
		// �� ȭ����� ���̰� ��������� ǥ���Ѵ�.
		else if ((snake_.head().X == food_position_.X&&snake_.head().Y == food_position_.Y) || (snake_.head().X == food_position_a.X&&snake_.head().Y == food_position_a.Y) || (snake_.head().X == food_position_b.X&&snake_.head().Y == food_position_b.Y))
		{
			putchar_at_xy(snake_.head().X, snake_.head().Y, 'O');
			score_++;

			// ȭ�鿡 �������� 

			go_to_xy(83, 12);
			printf("Your score: %d", score_);

			if ((snake_.head().X == food_position_.X) && (snake_.head().Y == food_position_.Y))
			{
				food_position_.X = 0;
				food_position_.Y = 0;
			}
			else if ((snake_.head().X == food_position_a.X) && (snake_.head().Y == food_position_a.Y))
			{
				food_position_a.X = 0;
				food_position_a.Y = 0;
			}
			else if ((snake_.head().X == food_position_b.X) && (snake_.head().Y == food_position_b.Y))
			{
				food_position_b.X = 0;
				food_position_b.Y = 0;
			}

		}
		// ���� ���̸� ���� ���� �ƴ϶�� �Ϲ������� �����Ѵ�.
		else
		{
			putchar_at_xy(snake_.head().X, snake_.head().Y, 'O');
			putchar_at_xy(snake_.tail().X, snake_.tail().Y, ' ');
			snake_.body().pop_back();
		}
		// ���� ���̸� �Ծ� ���ݴٸ� �ٽ� �����.
		if (is_no_food() == true)
		{
			make_food();
			display_.print_food(food_position_);
		}
		if (is_no_food_a() == true)
		{
			make_food_a();
			display_.print_food_a(food_position_a);
		}
		if (is_no_food_b() == true)
		{
			make_food_b();
			display_.print_food_b(food_position_b);
		}
	}

	return RETURN_SUCCESS;
}

// pause()
// ... ������ ��� ���߰� �޴��� �����ش�.
//
ReturnCode SnakeGame::pause()
{
	display_.print_prompt("(R)esume, (N)ew game, (S)top, (E)xit ");

	int key;
	do
	{
		key = getch();
	} while (key != 'r' && key != 'R' && key != 'n' && key != 'N' &&
		key != 's' && key != 'S' && key != 'e' && key != 'E');

	switch (key)
	{
	case 'r': case 'R':
		return RETURN_RESUME;
	case 'n': case 'N':
		return RETURN_NEWGAME;
	case 's': case 'S':
		return RETURN_STOP;
	case 'e': case 'E':
		return RETURN_EXIT;
	default:
		return RETURN_UNKNOWN;
	}
}

// stop()
//
ReturnCode SnakeGame::stop()
{
	display_.clear();

	// ȹ���� ������ ����Ѵ�.
	char msg[80];
	sprintf(msg, "Your score: %d ", score());
	display_.print_prompt(msg);

	// EnterŰ�� ������ ������ ���α׷��� �������� �ʴ´�.
	go_to_xy(55, 24);
	printf("Press [Enter] to quit...");
	while (getch() != ENTER)
		NOTHING;

	return RETURN_SUCCESS;
}

// make_food()
// ... ���̸� ���´�.
//
void SnakeGame::make_food()
{
	int x, y;

	srand((unsigned int)time(NULL));
	do
	{
		x = rand() % 77 + 1;    // 1 ~ 77
		y = rand() % 23 + 1;    // 1 ~ 23
	} while (is_valid_food_position(x, y) == false);

	food_position_.X = x;
	food_position_.Y = y;
}

void SnakeGame::make_food_a()
{
	int x, y;

	srand((unsigned int)time(NULL));
	do
	{
		x = rand() % 77 + 1;    // 1 ~ 77
		y = rand() % 23 + 1;    // 1 ~ 23
	} while (is_valid_food_position_a(x, y) == false);

	food_position_a.X = x;
	food_position_a.Y = y;
}

void SnakeGame::make_food_b()
{
	int x, y;

	srand((unsigned int)time(NULL));
	do
	{
		x = rand() % 77 + 1;    // 1 ~ 77
		y = rand() % 23 + 1;    // 1 ~ 23
	} while (is_valid_food_position_b(x, y) == false);

	food_position_b.X = x;
	food_position_b.Y = y;
}

// is_valid_food_position()
// ... ���̸� ���� �� �ִ� ��ġ�� true, �ƴϸ� false�� ��ȯ�Ѵ�.
//
bool SnakeGame::is_valid_food_position(int x, int y)
{
	list<Position>::const_iterator iter = snake_.body().begin();
	while (iter != snake_.body().end())
	{
		if ((x == iter->X) && (y == iter->Y))

			return false;
		iter++;

	}

	if ((x == food_position_a.X) || (x == food_position_b.X) || (y == food_position_a.Y) || (y == food_position_b.Y))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool SnakeGame::is_valid_food_position_a(int x, int y)
{
	list<Position>::const_iterator iter = snake_.body().begin();
	while (iter != snake_.body().end())
	{
		if ((x == iter->X) && (y == iter->Y))

			return false;
		iter++;

	}

	if ((x == food_position_.X) || (x == food_position_b.X) || (y == food_position_.Y) || (y == food_position_b.Y))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool SnakeGame::is_valid_food_position_b(int x, int y)
{
	list<Position>::const_iterator iter = snake_.body().begin();
	while (iter != snake_.body().end())
	{
		if ((x == iter->X) && (y == iter->Y))

			return false;
		iter++;

	}

	if ((x == food_position_a.X) || (x == food_position_.X) || (y == food_position_a.Y) || (y == food_position_.Y))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// is_no_food()
// ... ����ȭ�鿡 ���̰� ������ true, ������ false�� ��ȯ�Ѵ�.
//
bool SnakeGame::is_no_food()
{
	if (food_position_.X == 0 || food_position_.Y == 0)
		return true;
	else
		return false;
}
bool SnakeGame::is_no_food_a()
{
	if (food_position_a.X == 0 || food_position_a.Y == 0)
		return true;
	else
		return false;
}
bool SnakeGame::is_no_food_b()
{
	if (food_position_b.X == 0 || food_position_b.Y == 0)
		return true;
	else
		return false;
}



// score()
//
const SnakeGame::ScoreType SnakeGame::score() const
{
	return score_;
}
