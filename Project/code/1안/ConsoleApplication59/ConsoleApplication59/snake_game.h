#ifndef __SNAKE_GAME_H__
#define __SNAKE_GAME_H__

#include "common.h"
#include "display.h"
#include "snake.h"

class SnakeGame
{
public:  typedef/*unsigned*/ int ScoreType;

public:
	SnakeGame();

	void initialize();

	ReturnCode start();
	ReturnCode play();
	ReturnCode stop();

	void make_food();
	void make_food_a();
	void make_food_b();

public:
	ReturnCode pause();

	bool is_valid_food_position(int x, int y);
	bool is_valid_food_position_a(int x, int y);
	bool is_valid_food_position_b(int x, int y);
	bool is_no_food();
	bool is_no_food_a();
	bool is_no_food_b();

	const ScoreType score() const;
	//void display_score();
public:
	Snake snake_;
	Position food_position_;
	Position food_position_a;
	Position food_position_b;
	Display display_;
	ScoreType score_;
};

#endif