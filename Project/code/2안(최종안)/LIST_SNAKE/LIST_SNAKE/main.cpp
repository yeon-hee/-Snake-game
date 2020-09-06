#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;


#define BACK_SPACE       8
#define	ENTER   		13
#define	ESC				27
#define UP				72
#define DOWN			80
#define LEFT			75
#define RIGHT			77
#define PAGE_UP			73
#define PAGE_DOWN		81
#define DEL	    		83

#define SIZE_X 30
#define SIZE_Y 20

enum { HIDE, SHOW };
enum {
	BLACK,			
	DARK_BLUE,		
	DARK_GREEN,		
	DARK_SKY_BLUE,	
	DARK_RED,		
	DARK_VIOLET,	
	DARK_YELLOW,	
	GRAY,			
	DARK_GRAY,		
	BLUE,			
	GREEN,			
	SKY_BLUE,		
	RED,			
	VIOLET,			
	YELLOW,			
	WHITE,			
};

void CursorView(char show);
void gotoxy(int x, int y);
void SetColor(int color);

//화면 커서
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//좌표
void gotoxy(int x, int y) 
{
	COORD XY = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

//콘솔 색
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


struct Point {
	int x, y;
	bool operator ==(const Point &P) const
	{
		return (x == P.x && y == P.y);
	}
};

enum { EMPTY, HEAD, BODY, TAIL, ITEM, WALL, ITEM1, ITEM2 };
enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

class CDRAW
{
private:
	// 게임보드의 좌상단 좌표
	int nX, nY;

public:
	CDRAW();
	~CDRAW() { ; }

	void printData(int x, int y, int type);
	void printData(int x, int y, int type, int dir);
	void drawTime(time_t sec);
	void drawScore(int size);
	void drawSpeed(int speed);
	bool endMsg();
};


CDRAW::CDRAW()
{
	nX = (40 - SIZE_X - 1) / 2;
	nY = 12 - SIZE_Y / 2 - 1;
}

bool CDRAW::endMsg()
{
	const char *str1 = "     Game Over      ";
	const char *str2 = " One more game? y/n ";
	const char *str3 = "                    ";

	int len = strlen(str1);
	int x = 40 - len / 2;
	int ch, y = 10;

	gotoxy(x, y + 0); cout << str3;
	gotoxy(x, y + 1); cout << str1;
	gotoxy(x, y + 2); cout << str3;
	gotoxy(x, y + 3); cout << str2;
	gotoxy(x, y + 4); cout << str3;
	while (true)
	{
		ch = getch();
		if (ch == 'n' || ch == 'N' || ch == ESC) return false;
		else if (ch == 'y' || ch == 'Y') return true;
	}
}

void CDRAW::printData(int x, int y, int type)
{
	const int color[] = { BLACK, GREEN, GREEN, GREEN, RED, DARK_GRAY, DARK_BLUE, YELLOW };
	const char *shape[] = { "  ", "◀", "◎", "<>",  "♥", "▣", "★", "♣" };

	SetColor(color[type]);
	gotoxy((x + nX + 1) * 2, y + nY + 1);
	cout << shape[type];
	SetColor(GRAY);
}

void CDRAW::printData(int x, int y, int type, int dir)
{
	const int color[] = { BLACK, GREEN, GREEN, GREEN, RED, DARK_GRAY };
	const char *headShape[] = { "▲", "▼", "◀", "▶" };

	SetColor(color[type]);
	gotoxy((x + nX + 1) * 2, y + nY + 1);
	cout << headShape[dir];
	SetColor(GRAY);
}

void CDRAW::drawTime(time_t sec)
{
	int hh, mm;

	hh = sec / 3600;
	mm = (sec % 3600) / 60;
	sec = sec %= 60;

	SetColor(SKY_BLUE);
	gotoxy(nX * 2, 23);
	cout << hh << ':' << mm << ':' << sec;
	SetColor(GRAY);
}

void CDRAW::drawScore(int size)
{
	SetColor(VIOLET);
	gotoxy(nX * 2 + 20, 23);
	cout << "score : " << size;
	SetColor(GRAY);
}

void CDRAW::drawSpeed(int speed)
{
	SetColor(VIOLET);
	gotoxy(nX * 2 + 50, 23);
	cout << "Speed : " << speed;
	SetColor(GRAY);
}

struct Node
{
	Point p;
	Node *prev;
	Node *next;

	void showTail(CDRAW *pdr) {
		pdr->printData(p.x, p.y, TAIL);
	}

	void hideTail(CDRAW *pdr) {
		pdr->printData(p.x, p.y, EMPTY);
	}
};

class List
{
private:
	Node *Head;
	Node *Tail;

public:
	List();
	~List();

	void initNode();
	void insert(Point data);
	bool deleteData(CDRAW *pdr);
	bool deleteData();
	bool serch(Point pp);
	bool serch();
	void clear();
};

List::List()
{
	initNode();
}

List::~List()
{
	delete Head;
	delete Tail;
	Head = NULL;
	Tail = NULL;
	puts("~Goodbye~	");
}

void List::initNode()
{
	Head = new Node;
	Tail = new Node;

	Head->prev = NULL;
	Head->next = Tail;
	Tail->prev = Head;
	Tail->next = NULL;
}

void List::insert(Point data)
{
	Node *New;

	New = new Node;
	New->p = data;
	New->next = Head->next;
	New->next->prev = New;
	New->prev = Head;
	Head->next = New;
}

bool List::deleteData(CDRAW *pdr)
{
	Node *Del;

	if (Tail->prev == Head) return false;
	Del = Tail->prev;
	Tail->prev = Del->prev;
	Del->prev->next = Tail;
	Del->hideTail(pdr);
	Tail->prev->showTail(pdr);

	delete Del;
	return true;
}

bool List::deleteData()
{
	Node *Del;

	if (Tail->prev == Head) return false;
	Del = Tail->prev;
	Tail->prev = Del->prev;
	Del->prev->next = Tail;

	delete Del;
	return true;
}

void List::clear()
{
	while (deleteData());
}

bool List::serch(Point pp)
{
	Node *tmp = Head->next;
	for (tmp; tmp->next; tmp = tmp->next)
	{
		if (pp == tmp->p) return true;
	}
	return false;
}

bool List::serch()
{
	Node *tmp = Head->next;
	Point p = tmp->p;
	tmp = tmp->next;
	for (tmp; tmp->next; tmp = tmp->next)
	{
		if (p == tmp->p) return true;
	}
	return false;
}

class CSNAKE
{
private:
	CDRAW *pDraw;
	List list;
	Point nSnake;
	Point nItem, nItem1, nItem2;

	time_t t1, t2, t3;

	int nScore;
	int nSpeed;
	int dx, dy;
	int x, y;
	int dir;

	void drawTime();
	void initGame();
	void drawItem();
	void drawItem1();
	void drawItem2();
	void drawGameBoard();
	void makeSnake();
	void drawSnake();
	void upScore();
	bool moveSnake();
	bool checkItem();
	bool checkItem1();
	bool checkItem2();
	bool checkCrush();
	bool checkKey();
	int  getKey();

public:
	CSNAKE(CDRAW *pdr);
	~CSNAKE() { ; }

	bool runGame();
};

CSNAKE::CSNAKE(CDRAW *pdr)
{
	pDraw = pdr;
}

void CSNAKE::initGame()
{
	t1 = t2 = t3 = clock();
	nScore = 0;
	nSpeed = 200;
	x = SIZE_X / 2 + 1;
	y = SIZE_Y /2;//시작점 설정
	dx = -1;
	dy = 0;//방향 무조건 왼쪽으로
	dir = 2;
	drawGameBoard();
	makeSnake();
	drawItem();
	drawItem1();
	drawItem2();
	drawTime();
	pDraw->drawScore(nScore);
	pDraw->drawSpeed(nSpeed);
}

void CSNAKE::drawGameBoard()
{
	int i;
	for (i = 0; i < SIZE_Y + 2; i++)pDraw->printData(-1, i - 1, WALL);
	for (i = 0; i < SIZE_Y + 2; i++)pDraw->printData(SIZE_X, i - 1, WALL);
	for (i = 0; i < SIZE_X + 2; i++)pDraw->printData(i - 1, -1, WALL);
	for (i = 0; i < SIZE_X + 2; i++)pDraw->printData(i - 1, SIZE_Y, WALL);
}

void CSNAKE::makeSnake()
{
	int j = 2;

	nSnake.y = y;
	pDraw->printData(j + x, y, TAIL);
	nSnake.x = x + j--;
	list.insert(nSnake);

	pDraw->printData(j + x, y, BODY);
	nSnake.x = x + j--;
	list.insert(nSnake);

	pDraw->printData(j + x, y, HEAD);
	nSnake.x = x + j;
	list.insert(nSnake);
}

bool CSNAKE::checkCrush()
{
	if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y) return true;
	else if (list.serch()) return true;
	else return false;
}

void CSNAKE::drawItem()
{
	do {
		nItem.x = rand() % SIZE_X;
		nItem.y = rand() % SIZE_Y;
	} 
	while (list.serch(nItem) && list.serch(nItem1) && list.serch(nItem2) && (nItem == nItem1) && (nItem == nItem2) && (nItem1 == nItem2));
	pDraw->printData(nItem.x, nItem.y, ITEM);
}

void CSNAKE::drawItem1()
{
	do {
		nItem1.x = rand() % SIZE_X;
		nItem1.y = rand() % SIZE_Y;
		} 
	while (list.serch(nItem) && list.serch(nItem1) && list.serch(nItem2) && (nItem == nItem1) && (nItem == nItem2) && (nItem1 == nItem2));
	pDraw->printData(nItem1.x, nItem1.y, ITEM1);
}

void CSNAKE::drawItem2()
{
	do {
		nItem2.x = rand() % SIZE_X;
		nItem2.y = rand() % SIZE_Y;
	} while (list.serch(nItem) && list.serch(nItem1) && list.serch(nItem2) && (nItem == nItem1) && (nItem == nItem2) && (nItem1 == nItem2));
	pDraw->printData(nItem2.x, nItem2.y, ITEM2);
}

bool CSNAKE::checkItem()
{
	if (nItem == nSnake)  return true;
	else return false;
}

bool CSNAKE::checkItem1()
{
	if (nItem1 == nSnake)  return true;
	else return false;
}

bool CSNAKE::checkItem2()
{
	if (nItem2 == nSnake) return true;
	else return false;
}

void CSNAKE::upScore()
{
	pDraw->drawScore(++nScore);
	nSpeed > 50 ? nSpeed -= 1 : nSpeed;
	pDraw->drawSpeed(nSpeed);
}

void CSNAKE::drawSnake()
{
	Point p;
	pDraw->printData(x, y, BODY);
	x = p.x = nSnake.x + dx;
	y = p.y = nSnake.y + dy;
	pDraw->printData(x, y, HEAD, dir);
	nSnake = p;
	list.insert(p);
}

bool CSNAKE::moveSnake()
{
	drawSnake();
	if (checkItem()) {
		drawItem();
		upScore();
	}
	else if (checkItem1()) {
		drawItem1();
		upScore();
	}
	else if (checkItem2()) {
		drawItem2();
		upScore();
	}
	else {
		list.deleteData(pDraw);
	}

	return checkCrush();
}

void CSNAKE::drawTime()
{
	time_t sec = (clock() - t3) / 1000;
	pDraw->drawTime(sec);
	t2 = clock();
}

bool CSNAKE::runGame()
{
	int end = 0;
	system("cls");
	initGame();
	while (!end)
	{
		if (clock() - t2 >= 1000) drawTime();
		if (clock() - t1 >= nSpeed)
		{
			end = checkKey();
			if (moveSnake()) break;
			t1 = clock();
		}
		Sleep(10);
	}
	list.clear();
	if (end) return false;
	else return pDraw->endMsg();
}

int CSNAKE::getKey()
{
	int ch;

	ch = getch();
	if (ch == 0 || ch == 0xE0) ch = getch();

	return ch;
}

bool CSNAKE::checkKey()
{
	int ch;

	if (kbhit()) ch = getKey();
	else return 0;

	switch (ch)
	{
	case UP:
		dy == 0 ? dy = -1, dx = 0, dir = DIR_UP : dy;
		break;

	case DOWN:
		dy == 0 ? dy = 1, dx = 0, dir = DIR_DOWN : dy;
		break;

	case LEFT:
		dx == 0 ? dx = -1, dy = 0, dir = DIR_LEFT : dx;
		break;

	case RIGHT:
		dx == 0 ? dx = 1, dy = 0, dir = DIR_RIGHT : dx;
		break;

	case ESC: return 1;
	default: break;
	}
	return 0;
}

int main()
{
	srand((unsigned)time(NULL));
	CursorView(HIDE);

	CDRAW draw;
	CSNAKE snake(&draw);

	while (snake.runGame());

	CursorView(SHOW);
	return 0;
}
