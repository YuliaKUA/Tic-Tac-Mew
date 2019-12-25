#pragma once
#ifndef PLAYER
#define PLAYER

#include <cstdlib>
#include <iostream>
#include <Windows.h>

#include "TicTacToeGame.h"

using namespace std;
using namespace sf;

//////////////////
class Player // template for user and machine
{
public:
	virtual void setFigure(int figure) = 0;
	virtual int  getFigure() = 0;

	virtual void makeMove(TTTGame::Field & field, RenderWindow & window) = 0;
	virtual void makeMove(TTTGame::Field & field) = 0;

	virtual void reset() = 0;
};


///////////////////
class User : public Player
{
private:
	int mFigure_;

	Texture xPiece_;
public:
	Sprite playerSprite_;

	User() {
		this->mFigure_ = 0;
		this->xPiece_.loadFromFile(X_PIECE_FILEPATH);
	}

	void setFigure(int figure) { // cross
		this->mFigure_ = figure;
	}

	int getFigure() {
		return this->mFigure_;
	}

	void makeMove(TTTGame::Field & field) { }

	void makeMove(TTTGame::Field & field, RenderWindow & window) {
		//window.display();

		int cellNumber = 0;
		int x = -1, y = -1;

		while (!TTTGame::makeMove(field, this->mFigure_, x, y))
		{
			// read the coordinates of the cell field, depending on the location of the cursor
			if (IntRect(150, 75, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 1;
			}
			if (IntRect(273, 75, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 2;
			}
			if (IntRect(396, 75, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 3;
			}
			if (IntRect(519, 75, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 4;
			}
			if (IntRect(642, 75, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 5;
			}


			if (IntRect(150, 198, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 6;
			}
			if (IntRect(273, 198, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 7;
			}
			if (IntRect(396, 198, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 8;
			}
			if (IntRect(519, 198, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 9;
			}
			if (IntRect(642, 198, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 10;
			}


			if (IntRect(150, 321, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 11;
			}
			if (IntRect(273, 321, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 12;
			}
			if (IntRect(396, 321, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 13;
			}
			if (IntRect(519, 321, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 14;
			}
			if (IntRect(642, 321, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 15;
			}


			if (IntRect(150, 444, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 16;
			}
			if (IntRect(273, 444, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 17;
			}
			if (IntRect(396, 444, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 18;
			}
			if (IntRect(519, 444, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 19;
			}
			if (IntRect(642, 444, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 20;
			}


			if (IntRect(150, 567, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 21;
			}
			if (IntRect(273, 567, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 22;
			}
			if (IntRect(396, 567, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 23;
			}
			if (IntRect(519, 567, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 24;
			}
			if (IntRect(642, 567, 112, 112).contains(Mouse::getPosition(window))) {
				cellNumber = 25;
			}

			playerSprite_.setTexture(xPiece_);

			Event event;
			window.pollEvent(event);
			// if the left mouse button is pressed - draw a shape
			if (event.type == Event::MouseButtonPressed)
			{
				if (cellNumber == 1) {
					playerSprite_.setPosition(150, 75);
					window.draw(playerSprite_);

					x = 0;
					y = 0;
				}
				if (cellNumber == 2) {
					playerSprite_.setPosition(273, 75);
					window.draw(playerSprite_);
					x = 1;
					y = 0;
				}
				if (cellNumber == 3) {
					playerSprite_.setPosition(396, 75);
					window.draw(playerSprite_);
					x = 2;
					y = 0;
				}
				if (cellNumber == 4) {
					playerSprite_.setPosition(519, 75);
					window.draw(playerSprite_);
					x = 3;
					y = 0;
				}
				if (cellNumber == 5) {
					playerSprite_.setPosition(642, 75);
					window.draw(playerSprite_);
					x = 4;
					y = 0;
				}



				if (cellNumber == 6) {
					playerSprite_.setPosition(150, 198);
					window.draw(playerSprite_);
					x = 0;
					y = 1;
				}
				if (cellNumber == 7) {
					playerSprite_.setPosition(273, 198);
					window.draw(playerSprite_);
					x = 1;
					y = 1;
				}
				if (cellNumber == 8) {
					playerSprite_.setPosition(396, 198);
					window.draw(playerSprite_);
					x = 2;
					y = 1;
				}
				if (cellNumber == 9) {
					playerSprite_.setPosition(519, 198);
					window.draw(playerSprite_);
					x = 3;
					y = 1;
				}
				if (cellNumber == 10) {
					playerSprite_.setPosition(642, 198);
					window.draw(playerSprite_);
					x = 4;
					y = 1;
				}


				if (cellNumber == 11) {
					playerSprite_.setPosition(150, 321);
					window.draw(playerSprite_);
					x = 0;
					y = 2;
				}
				if (cellNumber == 12) {
					playerSprite_.setPosition(273, 321);
					window.draw(playerSprite_);
					x = 1;
					y = 2;
				}
				if (cellNumber == 13) {
					playerSprite_.setPosition(396, 321);
					window.draw(playerSprite_);
					x = 2;
					y = 2;
				}
				if (cellNumber == 14) {
					playerSprite_.setPosition(519, 321);
					window.draw(playerSprite_);
					x = 3;
					y = 2;
				}
				if (cellNumber == 15) {
					playerSprite_.setPosition(642, 321);
					window.draw(playerSprite_);
					x = 4;
					y = 2;
				}


				if (cellNumber == 16) {
					playerSprite_.setPosition(150, 444);
					window.draw(playerSprite_);
					x = 0;
					y = 3;
				}
				if (cellNumber == 17) {
					playerSprite_.setPosition(273, 444);
					window.draw(playerSprite_);
					x = 1;
					y = 3;
				}
				if (cellNumber == 18) {
					playerSprite_.setPosition(396, 444);
					window.draw(playerSprite_);
					x = 2;
					y = 3;
				}
				if (cellNumber == 19) {
					playerSprite_.setPosition(519, 444);
					window.draw(playerSprite_);
					x = 3;
					y = 3;
				}
				if (cellNumber == 20) {
					playerSprite_.setPosition(642, 444);
					window.draw(playerSprite_);
					x = 4;
					y = 3;
				}


				if (cellNumber == 21) {
					playerSprite_.setPosition(150, 567);
					window.draw(playerSprite_);
					x = 0;
					y = 4;
				}
				if (cellNumber == 22) {
					playerSprite_.setPosition(273, 567);
					window.draw(playerSprite_);
					x = 1;
					y = 4;
				}
				if (cellNumber == 23) {
					playerSprite_.setPosition(396, 567);
					window.draw(playerSprite_);
					x = 2;
					y = 4;
				}
				if (cellNumber == 24) {
					playerSprite_.setPosition(519, 567);
					window.draw(playerSprite_);
					x = 3;
					y = 4;
				}
				if (cellNumber == 25) {
					playerSprite_.setPosition(642, 567);
					window.draw(playerSprite_);
					x = 4;
					y = 4;

				}

			}

		}

	}


	void reset() { }
};


///////////////////////////////////
class Bot : public Player
{
private:
	int mFigure_;

	// break the winning line
	bool interruptEnemy(TTTGame::Field & field)
	{
		int enemy;
		if (this->mFigure_ == TTT_CIRCLE)
			enemy = TTT_CROSS;
		else
			enemy = TTT_CIRCLE;

		// horizontally
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			if (field[i][0] == enemy && field[i][1] == enemy && field[i][2] == enemy
				&& field[i][3] == enemy && field[i][4] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, 4, i);
				return true;
			}
			if (field[i][0] == enemy && field[i][1] == enemy && field[i][2] == enemy
				&& field[i][4] == enemy && field[i][3] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, 3, i);
				return true;
			}if (field[i][0] == enemy && field[i][1] == enemy && field[i][4] == enemy
				&& field[i][3] == enemy && field[i][2] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, 2, i);
				return true;
			}if (field[i][0] == enemy && field[i][4] == enemy && field[i][2] == enemy
				&& field[i][3] == enemy && field[i][1] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, 1, i);
				return true;
			}if (field[i][4] == enemy && field[i][1] == enemy && field[i][2] == enemy
				&& field[i][3] == enemy && field[i][0] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, 0, i);
				return true;
			}
		}

		// vertically
		for (int i = 0; i < TTT_FIELDSIZE; i++)
		{
			if (field[0][i] == enemy && field[1][i] == enemy && field[2][i] == enemy
				&& field[3][i] == enemy && field[4][i] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, i, 4);
				return true;
			}
			if (field[0][i] == enemy && field[1][i] == enemy && field[2][i] == enemy
				&& field[4][i] == enemy && field[3][i] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, i, 3);
				return true;
			}
			if (field[0][i] == enemy && field[1][i] == enemy && field[4][i] == enemy
				&& field[3][i] == enemy && field[2][i] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, i, 2);
				return true;
			}
			if (field[0][i] == enemy && field[4][i] == enemy && field[2][i] == enemy
				&& field[3][i] == enemy && field[1][i] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, i, 1);
				return true;
			}
			if (field[4][i] == enemy && field[1][i] == enemy && field[2][i] == enemy
				&& field[3][i] == enemy && field[0][i] == TTT_EMPTY)
			{
				TTTGame::makeMove(field, this->mFigure_, i, 0);
				return true;
			}
		}

		// on the main diagonal
		int diagonal1[TTT_FIELDSIZE];
		for (int i = 0; i < TTT_FIELDSIZE; i++)
			diagonal1[i] = field[i][i];

		if (diagonal1[0] == enemy && diagonal1[1] == enemy && diagonal1[2] == enemy
			&& diagonal1[3] == enemy && diagonal1[4] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 4, 4));
			return true;
		}
		if (diagonal1[0] == enemy && diagonal1[1] == enemy && diagonal1[2] == enemy
			&& diagonal1[4] == enemy && diagonal1[3] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 3, 3));
			return true;
		}
		if (diagonal1[0] == enemy && diagonal1[1] == enemy && diagonal1[4] == enemy
			&& diagonal1[3] == enemy && diagonal1[2] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 2, 2));
			return true;
		}
		if (diagonal1[0] == enemy && diagonal1[4] == enemy && diagonal1[2] == enemy
			&& diagonal1[3] == enemy && diagonal1[1] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 1, 1));
			return true;
		}
		if (diagonal1[4] == enemy && diagonal1[1] == enemy && diagonal1[2] == enemy
			&& diagonal1[3] == enemy && diagonal1[0] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 0, 0));
			return true;
		}

		// on the side diagonal
		int diagonal2[TTT_FIELDSIZE] = { field[0][4], field[1][3], field[2][2], field[3][1], field[4][0] };

		if (diagonal2[0] == enemy && diagonal2[1] == enemy && diagonal2[2] == enemy
			&& diagonal2[3] == enemy && diagonal2[4] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 0, 4));
			return true;
		}
		if (diagonal2[0] == enemy && diagonal2[1] == enemy && diagonal2[2] == enemy
			&& diagonal2[4] == enemy && diagonal2[3] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 1, 3));
			return true;
		}
		if (diagonal2[0] == enemy && diagonal2[1] == enemy && diagonal2[4] == enemy
			&& diagonal2[3] == enemy && diagonal2[2] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 2, 2));
			return true;
		}
		if (diagonal2[0] == enemy && diagonal2[4] == enemy && diagonal2[2] == enemy
			&& diagonal2[3] == enemy && diagonal2[1] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 3, 1));
			return true;
		}
		if (diagonal2[4] == enemy && diagonal2[1] == enemy && diagonal2[2] == enemy
			&& diagonal2[3] == enemy && diagonal2[0] == TTT_EMPTY)
		{
			while (!TTTGame::makeMove(field, this->mFigure_, 4, 0));
			return true;
		}

		return false;
	}

	// make a random move
	void makeRandomMove(TTTGame::Field & field)
	{
		int x = -1, y = -1;
		while (!TTTGame::makeMove(field, this->mFigure_, x, y))
		{
			x = rand() % 5;
			y = rand() % 5;
		}
	}

public:
	Bot() {
		this->mFigure_ = 0;
	}

	void setFigure(int figure) {
		this->mFigure_ = figure;
	}

	int getFigure() {
		return this->mFigure_;
	}

	void makeMove(TTTGame::Field & field) {
		if (!this->interruptEnemy(field))
			this->makeRandomMove(field);
	}

	void makeMove(TTTGame::Field & field, RenderWindow & window) {
		if (!this->interruptEnemy(field))
			this->makeRandomMove(field);
	}

	void reset() {}
};

#endif
