// Labyrinth.cpp : Defines the entry point for the console application.
//


/*Игра лабиринт :
играющий перемещается в двухмерном пространстве по помещениям здания, план которого играющему неизвестен.
Начиная с произвольного помещения, путешественник должен найти выход из здания.
Каждое помещение может иметь четыре двери : север, восток, юг, запад и соединяться с другими помещениями.
План здания необходимо сгенерировать случайно.Порядок следования помещений в списке должен быть произвольным.
Находясь в N - ом помещении, игрок может получить подсказку о правильном направлении движения,
если выполнит тестовое задание по теме "Программирование на языке высокого уровня"
Предложите и реализуйте не менее трех вариантов расширения функциональности этой игры
(например, автоматическое или ручное прохождение роботом лабиринта, несколько выходов и т.п.)
*/
#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>

#define KEY_W 119 ///< Кнопка вперёд.
#define KEY_A 97 ///< Кнопка влево.
#define KEY_S 115 ///< Кнопка назад.
#define KEY_D 100 ///< Кнопка вправо.

#define KEY_E 101 ///< Кнопка E(Exit - выход).
#define KEY_ESC 27 ///< Кнопка Escape.

#define KEY_H 104 ///< Кнопка H(Help - помощь).

#define N 20 ///< Размер отображаемого игрового поля.

int currentX = 0; ///< Текущая координата X путешественника.
int currentY = 0; ///< Текущая координата Y путешественника.

/**
  * Тип отображаемого объекта(пустота, стена, путешественник).
  */
enum object {
	nothing = 0,
	wall = 1,
	voyager = 2
};

object buffer[N][N]; ///< Буфер кадра. Необходим для формирования изображения.

/**
  * Установить точку в буфере.
  */
void setPoint(int x, int y, object type)
{
	buffer[y][x] = type;
}

/**
  * Очистить буфер.
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
  * Вывести содержимое буфера на экран.
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
  * Переместить путешественника на одну позицию вперёд.
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
  * Переместить путешественника на одну позицию назад.
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
  * Переместить путешественника на одну позицию влево.
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
  * Переместить путешественника на одну позицию вправо.
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
  * Обработчик кнопки "Помощь".
  */
void help()
{
	printf("help");
}

/**
  * Опросить клавиатуру.
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
	//Рисуем границы лабиринта
	for (int i = 0; i < N; i++)
	{
		setPoint(i, 0, object::wall); ///< Верхняя граница.
		setPoint(i, N - 1, object::wall); ///< Нижняя граница.
		setPoint(0, i, object::wall); ///< Левая граница.
		setPoint(N - 1, i, object::wall); ///< Правая граница.
	}

	//int h = 4; ///< Высота комнаты.
	//int crossWallsCount = N/h; ///< Количетсво поперечных стен.
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
  * Инициализация игры.
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
  * Главная функция программы - точка входа(С этой функции начинается выполнение программы).
  */
int main()
{
	initGame();
	drawBuffer();
	pollKeyboard();

	return 0;
}

