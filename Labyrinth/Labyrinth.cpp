// Labyrinth.cpp : Defines the entry point for the console application.
//


/*���� �������� :
�������� ������������ � ���������� ������������ �� ���������� ������, ���� �������� ��������� ����������.
������� � ������������� ���������, �������������� ������ ����� ����� �� ������.
������ ��������� ����� ����� ������ ����� : �����, ������, ��, ����� � ����������� � ������� �����������.
���� ������ ���������� ������������� ��������.������� ���������� ��������� � ������ ������ ���� ������������.
�������� � N - �� ���������, ����� ����� �������� ��������� � ���������� ����������� ��������,
���� �������� �������� ������� �� ���� "���������������� �� ����� �������� ������"
���������� � ���������� �� ����� ���� ��������� ���������� ���������������� ���� ����
(��������, �������������� ��� ������ ����������� ������� ���������, ��������� ������� � �.�.)
*/
#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>

#define KEY_W 119 ///< ������ �����.
#define KEY_A 97 ///< ������ �����.
#define KEY_S 115 ///< ������ �����.
#define KEY_D 100 ///< ������ ������.

#define KEY_E 101 ///< ������ E(Exit - �����).
#define KEY_ESC 27 ///< ������ Escape.

#define KEY_H 104 ///< ������ H(Help - ������).

#define N 20 ///< ������ ������������� �������� ����.

int currentX = 0; ///< ������� ���������� X ���������������.
int currentY = 0; ///< ������� ���������� Y ���������������.

/**
  * ��� ������������� �������(�������, �����, ��������������).
  */
enum object {
	nothing = 0,
	wall = 1,
	voyager = 2
};

object buffer[N][N]; ///< ����� �����. ��������� ��� ������������ �����������.

/**
  * ���������� ����� � ������.
  */
void setPoint(int x, int y, object type)
{
	buffer[y][x] = type;
}

/**
  * �������� �����.
  */
void clearBuffer()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			buffer[i][j] = object::nothing;
		}
	}
	system("CLS");
}

void clearPlayer()
{
	setPoint(currentX, currentY, object::nothing);
	system("CLS");
}

/**
  * ������� ���������� ������ �� �����.
  */
void drawBuffer()
{
	printf(" ");
	for (int i = 0; i < N; i++)
	{
		printf("-");
	}

	printf("\n");

	for (int i = 0; i < N; i++)
	{
		printf("|");
		for (int j = 0; j < N; j++)
		{
			switch (buffer[i][j])
			{
			case object::voyager:
				printf("*");
				break;
			case object::wall:
				printf("#");
				break;
			default:
				printf(" ");
				break;
			}
		}
		printf("|");
		printf("\n");
	}

	printf(" ");
	for (int i = 0; i < N; i++)
	{
		printf("-");
	}
}

/**
  * ����������� ��������������� �� ���� ������� �����.
  */
void moveUp()
{
	if (currentY > 0)
	{
		clearPlayer();
		currentY--;
		setPoint(currentX, currentY, object::voyager);
		drawBuffer();
	}
}

/**
  * ����������� ��������������� �� ���� ������� �����.
  */
void moveDown()
{
	if (currentY < N - 1)
	{
		clearPlayer();
		currentY++;
		setPoint(currentX, currentY, object::voyager);
		drawBuffer();
	}
}

/**
  * ����������� ��������������� �� ���� ������� �����.
  */
void moveLeft()
{
	if (currentX > 0)
	{
		clearPlayer();
		currentX--;
		setPoint(currentX, currentY, object::voyager);
		drawBuffer();
	}
}

/**
  * ����������� ��������������� �� ���� ������� ������.
  */
void moveRight()
{
	if (currentX < N - 1)
	{
		clearPlayer();
		currentX++;
		setPoint(currentX, currentY, object::voyager);
		drawBuffer();
	}
}

/**
  * ���������� ������ "������".
  */
void help()
{
	printf("help");
}

/**
  * �������� ����������.
  */
void pollKeyboard()
{
	int keyCode;
	do
	{
		keyCode = _getch();

		switch (keyCode)
		{
		case KEY_W:
		{
			moveUp();
			break;
		}
		case KEY_A:
		{
			moveLeft();
			break;
		}
		case KEY_S:
		{
			moveDown();
			break;
		}
		case KEY_D:
		{
			moveRight();
			break;
		}
		case KEY_H:
		{
			help();
			break;
		}
		}
	} while (keyCode != KEY_E && keyCode != KEY_ESC);
}

void generateRooms()
{
	//������ ������� ���������
	for (int i = 0; i < N; i++)
	{
		setPoint(i, 0, object::wall); ///< ������� �������.
		setPoint(i, N - 1, object::wall); ///< ������ �������.
		setPoint(0, i, object::wall); ///< ����� �������.
		setPoint(N - 1, i, object::wall); ///< ������ �������.
	}

	//int h = 4; ///< ������ �������.
	//int crossWallsCount = N/h; ///< ���������� ���������� ����.
	//
	//for (int j = 0; j < crossWallsCount; j++)
	//{
	//	for (int i = 0; i < N; i++)
	//	{
	//		setPoint(i, h * j, object::wall);
	//	}
	//}
}

/**
  * ������������� ����.
  */
void initGame()
{
	srand((unsigned)time(NULL));
	clearBuffer();

	generateRooms();

	currentX = rand() % N;
	currentY = rand() % N;
	setPoint(currentX, currentY, object::voyager);
}

/**
  * ������� ������� ��������� - ����� �����(� ���� ������� ���������� ���������� ���������).
  */
int main()
{
	initGame();
	drawBuffer();
	pollKeyboard();

	return 0;
}

