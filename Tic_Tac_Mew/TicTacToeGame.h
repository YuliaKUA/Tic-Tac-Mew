// алгоритм
#pragma once
#ifndef TICTACTOE_GAME
#define TICTACTOE_GAME

#include <iostream>
#include "DEFINITIONS.h"

using namespace std;
using namespace sf;

namespace TTTGame
{
	//создаем новый тип - поле размером 5х5
	typedef int Field[TTT_FIELDSIZE][TTT_FIELDSIZE];

	//заполняем все клеточки 0
	void init(Field & field)
	{
		for (int i = 0; i < TTT_FIELDSIZE; i++)
			for (int j = 0; j < TTT_FIELDSIZE; j++)
				field[i][j] = TTT_EMPTY;
	}

	//!!!!!!!!!
	//функция печати поля
	/*void print(Field & field)
	{
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			for (int j = 0; j < TTT_FIELDSIZE; j++)
			{
				if (j != 0)
					cout << '|';

				cout << ' ' << field[i][j] << ' ';
			}
			if (i != TTT_FIELDSIZE - 1)
				cout << endl << "------------------" << endl;
			else
				cout << endl;
		}
	}*/

	// сделать ход, присвоить полю 1 или 2
	// проверяет можем ли мы сделать ход
	bool makeMove(Field & field, int who, int wherex, int wherey) {
		if (wherex < 0 || wherex >= TTT_FIELDSIZE)
			return false;
		if (wherey < 0 || wherey >= TTT_FIELDSIZE)
			return false;

		if (field[wherey][wherex] != TTT_EMPTY)
			return false;

		field[wherey][wherex] = who;
		return true;
	}


	//для монтекарло
	bool makeMove(Field & field, int who, int wherex, int wherey, RenderWindow & window, Texture tex)
	{

		if (wherex < 0 || wherex >= TTT_FIELDSIZE)
			return false;
		if (wherey < 0 || wherey >= TTT_FIELDSIZE)
			return false;

		if (field[wherey][wherex] != TTT_EMPTY)
			return false;

		field[wherey][wherex] = who;

		// рисуем нолик в зависимости от координат
		if (who == TTT_CIRCLE) {
			Sprite oSprite(tex);

			if (wherey == 0 && wherex == 0) {
				oSprite.setPosition(150, 75);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 0 && wherex == 1) {
				oSprite.setPosition(273, 75);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 0 && wherex == 2) {
				oSprite.setPosition(396, 75);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 0 && wherex == 3) {
				oSprite.setPosition(519, 75);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 0 && wherex == 4) {
				oSprite.setPosition(642, 75);
				window.draw(oSprite);
				return true;
			}


			if (wherey == 1 && wherex == 0) {
				oSprite.setPosition(150, 198);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 1 && wherex == 1) {
				oSprite.setPosition(273, 198);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 1 && wherex == 2) {
				oSprite.setPosition(396, 198);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 1 && wherex == 3) {
				oSprite.setPosition(519, 198);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 1 && wherex == 4) {
				oSprite.setPosition(642, 198);
				window.draw(oSprite);
				return true;
			}


			if (wherey == 2 && wherex == 0) {
				oSprite.setPosition(150, 321);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 2 && wherex == 1) {
				oSprite.setPosition(273, 321);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 2 && wherex == 2) {
				oSprite.setPosition(396, 321);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 2 && wherex == 3) {
				oSprite.setPosition(519, 321);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 2 && wherex == 4) {
				oSprite.setPosition(642, 321);
				window.draw(oSprite);
				return true;
			}


			if (wherey == 3 && wherex == 0) {
				oSprite.setPosition(150, 444);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 3 && wherex == 1) {
				oSprite.setPosition(273, 444);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 3 && wherex == 2) {
				oSprite.setPosition(396, 444);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 3 && wherex == 3) {
				oSprite.setPosition(519, 444);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 3 && wherex == 4) {
				oSprite.setPosition(642, 444);
				window.draw(oSprite);
				return true;
			}


			if (wherey == 4 && wherex == 0) {
				oSprite.setPosition(150, 567);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 4 && wherex == 1) {
				oSprite.setPosition(273, 567);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 4 && wherex == 2) {
				oSprite.setPosition(396, 567);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 4 && wherex == 3) {
				oSprite.setPosition(519, 567);
				window.draw(oSprite);
				return true;
			}
			if (wherey == 4 && wherex == 4) {
				oSprite.setPosition(642, 567);
				window.draw(oSprite);
				return true;
			}
			window.display();
		}
	}

	// проверка на победу
	int checkWin(Field & field, RenderWindow & window)
	{
		//по вертикали
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			if (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[1][i] != TTT_EMPTY
				&& field[2][i] == field[3][i] && field[3][i] == field[4][i]) {

				if (field[2][i] == 2) {
					Texture xPieceVert;
					xPieceVert.loadFromFile(WIN_CROSS_VERT);
					Sprite xSpriteVert(xPieceVert);
					xSpriteVert.setPosition((i)*(112 + 11) + 150, 75);
					window.draw(xSpriteVert);
				}
				else if (field[2][i] == 1) {
					Texture oPieceVert;
					oPieceVert.loadFromFile(WIN_CIRCLE_VERT);
					Sprite oSpriteVert(oPieceVert);
					oSpriteVert.setPosition((i)*(112 + 11) + 150, 75);
					window.draw(oSpriteVert);
				}

				return field[2][i];
			}
		}

		//по горизонтали
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			if (field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][1] != TTT_EMPTY
				&& field[i][2] == field[i][3] && field[i][3] == field[i][4]) {

				if (field[i][2] == 2) {
					Texture xPieceHor;
					xPieceHor.loadFromFile(WIN_CROSS_HOR);
					Sprite xSpriteHor(xPieceHor);
					xSpriteHor.setPosition(150, 75 + (i)*(112 + 11));
					window.draw(xSpriteHor);
				}
				else if (field[i][2] == 1) {
					Texture oPieceHor;
					oPieceHor.loadFromFile(WIN_CIRCLE_VERT);
					Sprite oSpriteHor(oPieceHor);
					oSpriteHor.setPosition(150, 75 + (i)*(112 + 11));
					window.draw(oSpriteHor);
				}

				return field[i][2];
			}
		}

		//по диагоналям
		if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[2][2] != TTT_EMPTY
			&& field[2][2] == field[3][3] && field[3][3] == field[4][4]) {
			if (field[2][2] == 2) {
				Texture xPieceDiag1;
				xPieceDiag1.loadFromFile(WIN_CROSS_DIAGONAL_1);
				Sprite xSpriteDiag1(xPieceDiag1);
				xSpriteDiag1.setPosition(150, 75);
				window.draw(xSpriteDiag1);
			}
			else if (field[2][2] == 1) {
				Texture oPieceDiag1;
				oPieceDiag1.loadFromFile(WIN_CIRCLE_DIAGONAL_1);
				Sprite oSpriteDiag1(oPieceDiag1);
				oSpriteDiag1.setPosition(150, 75);
				window.draw(oSpriteDiag1);
			}

			return field[2][2];
		}

		if (field[0][4] == field[1][3] && field[1][3] == field[2][2] && field[2][2] != TTT_EMPTY
			&& field[2][2] == field[3][1] && field[3][1] == field[0][4]) {
			if (field[0][4] == 2) {
				Texture xPieceDiag2;
				xPieceDiag2.loadFromFile(WIN_CROSS_DIAGONAL_2);
				Sprite xSpriteDiag2(xPieceDiag2);
				xSpriteDiag2.setPosition(150, 75);
				window.draw(xSpriteDiag2);
			}
			else if (field[0][4] == 1) {
				Texture oPieceDiag2;
				oPieceDiag2.loadFromFile(WIN_CIRCLE_DIAGONAL_2);
				Sprite oSpriteDiag2(oPieceDiag2);
				oSpriteDiag2.setPosition(150, 75);
				window.draw(oSpriteDiag2);
			}
			return field[2][2];
		}

		//нет комбинации выигрышной
		return TTT_EMPTY;
	}

	int checkWin(Field & field)
	{
		//по вертикали
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			if (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[1][i] != TTT_EMPTY
				&& field[2][i] == field[3][i] && field[3][i] == field[4][i])
				return field[2][i];
		}

		//по горизонтали
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			if (field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][1] != TTT_EMPTY
				&& field[i][2] == field[i][3] && field[i][3] == field[i][4])
				return field[i][2];

		}

		//по диагоналям
		if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[2][2] != TTT_EMPTY
			&& field[2][2] == field[3][3] && field[3][3] == field[4][4])
			return field[2][2];


		if (field[0][4] == field[1][3] && field[1][3] == field[2][2] && field[2][2] != TTT_EMPTY
			&& field[2][2] == field[3][1] && field[3][1] == field[0][4])
			return field[2][2];

		//нет комбинации выигрышной
		return TTT_EMPTY;
	}

	//проверка можно ли сделать ход
	bool isPlayable(Field & field, RenderWindow & window)
	{
		if (checkWin(field, window)) {
			//window.display();
			return false;
		}

		for (int i = 0; i < TTT_FIELDSIZE; i++)
			for (int j = 0; j < TTT_FIELDSIZE; j++)
				if (field[i][j] == TTT_EMPTY)
					return true;

		return false;
	}

	bool isPlayable(Field & field)
	{
		if (checkWin(field)) {
			return false;
		}

		for (int i = 0; i < TTT_FIELDSIZE; i++)
			for (int j = 0; j < TTT_FIELDSIZE; j++)
				if (field[i][j] == TTT_EMPTY)
					return true;

		return false;
	}
}

#endif