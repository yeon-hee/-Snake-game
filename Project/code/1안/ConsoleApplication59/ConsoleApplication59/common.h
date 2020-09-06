#ifndef __COMMON_H__
#define __COMMON_H__

#include <Windows.h>

#define NOTHING

typedef enum
{
	RETURN_EXIT = -1,       // ���α׷� ����
	RETURN_FATAL = -1,       // ����
	RETURN_SUCCESS = 0,       // ����
	RETURN_FAILURE = 1,       // ����
	RETURN_UNKNOWN,       // �� �� ����
	RETURN_RESUME,       // �ٽ� ���
	RETURN_NEWGAME,       // �� ����
	RETURN_STOP,       // ���� ����
	RETURN_FOOD,       // ���̸� ����
	RETURN_WALL                 // ���� �ε���
} ReturnCode;

typedef enum
{
	UP = 72,                 // ����Ű ��
	DOWN = 80,                 // ����Ű �Ʒ�
	LEFT = 75,                 // ����Ű ����
	RIGHT = 77,                 // ����Ű ������
	ENTER = 13,                 // ���� Ű
	ESC = 27                  // ESC Ű
} Keyboard;

typedef COORD Position;

static const bool FOREVER = true;
const  static int GAME_SPEED = 100;//���� �۾������� ������//static const


/*extern*/ void go_to_xy(int x, int y);
/*extern*/ void putchar_at_xy(int x, int y, char ch);
/*void putchar_at_xy_a(int x, int y, char ch);
void putchar_at_xy_b(int x, int y, char ch);*/

#endif	