// алгоритм
#pragma once
#ifndef MONTECARLOBOT
#define MONTECARLOBOT

#include <iostream>
#include <vector>
#include "Player.h"
#include "TicTacToeGame.h"

using namespace std;
using namespace sf;

///////////////////////
typedef struct MCBTreeNode
{
	int player_ = 0;

	int moveX_ = -1;
	int moveY_ = -1;

	int wins_ = 0;
	int attempts_ = 0; //попытки

	MCBTreeNode * parent_ = nullptr;
	vector <MCBTreeNode *>  nodes_;

} MCBTreeNode;



////////////////////////
class MonteCarloBot : public Player
{
private:
	int mFigure_;

	//Состояние поля на предыдущем шаге
	TTTGame::Field mPreviousStep_;

	//Поиск следующего шага
	void  findNewStep(TTTGame::Field & field, int & someX, int & someY)
	{
		for (int y = 0; y < TTT_FIELDSIZE; y++)
			for (int x = 0; x < TTT_FIELDSIZE; x++)
				if (field[y][x] != this->mPreviousStep_[y][x]) {
					someX = x;
					someY = y;
				}

		for (int y = 0; y < TTT_FIELDSIZE; y++)
			for (int x = 0; x < TTT_FIELDSIZE; x++)
				this->mPreviousStep_[y][x] = field[y][x];
	}

	MCBTreeNode * mTree_; //дерево монте-карло отыгранное
	MCBTreeNode * mCurrent_; //дерево текущего состояния

public:
	//Конструктор
	MonteCarloBot()
	{
		this->mFigure_ = 0; //крестик или нолик
		this->mTree_ = new MCBTreeNode;
		this->mCurrent_ = this->mTree_;
		TTTGame::init(this->mPreviousStep_);
	}

	void setFigure(int figure) { //установить 1 или 2
		this->mFigure_ = figure;
	}

	int getFigure() { // вернуть фигуру игрока
		return this->mFigure_;
	}

	void makeMove(TTTGame::Field & field) { }

	void makeMove(TTTGame::Field & someField, RenderWindow & window) { //сделать ход

		//добавить узел с новым ходом
		//алгоритм выбирает ход своего противника. 
		//Если такой ход существует — мы его выберем, если нет — добавим
		bool exist = false;

		int enemyX = -1, enemyY = -1; //координаты врага
		this->findNewStep(someField, enemyX, enemyY);

		for (MCBTreeNode * node : this->mCurrent_->nodes_)
		{
			if (node->moveX_ == enemyX && node->moveY_ == enemyY)
			{
				exist = true;
				this->mCurrent_ = node;
			}
		}

		if (!exist)
		{
			MCBTreeNode * enemymove = new MCBTreeNode;
			enemymove->parent_ = this->mCurrent_;
			enemymove->moveX_ = enemyX;
			enemymove->moveY_ = enemyY;
			enemymove->player_ = (this->mFigure_ == TTT_CROSS) ? TTT_CIRCLE : TTT_CROSS;
			this->mCurrent_->nodes_.push_back(enemymove);
			this->mCurrent_ = enemymove;
		}

		// 1. выбрать узел с наибольшим количеством побед
		MCBTreeNode * bestnode = this->mCurrent_;
		for (MCBTreeNode * node : this->mCurrent_->nodes_)
		{
			if (((double)node->wins_ / node->attempts_) > ((double)bestnode->wins_ / bestnode->attempts_))
				bestnode = node;
		}

		// 2. расширение - создать новый узел
		//К выбранному узлу с ходом противника мы добавим узел 
		//со своим ходом и с нулевыми результатами
		MCBTreeNode * newnode = new MCBTreeNode;
		newnode->parent_ = bestnode;
		newnode->player_ = this->mFigure_;
		this->mCurrent_->nodes_.push_back(newnode);

		// 3. симуляция игры
		//Отыграем партию от текущего состояния игрового поля до чей-либо победы. 
		//Отсюда мы возьмём только первый ход (т.е. свой ход) и результаты
		TTTGame::Field field;
		for (int y = 0; y < TTT_FIELDSIZE; y++)
			for (int x = 0; x < TTT_FIELDSIZE; x++)
				field[y][x] = someField[y][x];

		Player * bot1 = new Bot();
		bot1->setFigure((this->mFigure_ == TTT_CROSS) ? TTT_CIRCLE : TTT_CROSS);
		Player * bot2 = new Bot();
		bot2->setFigure(this->mFigure_);

		Player * current = bot2;

		while (TTTGame::isPlayable(field))
		{
			current->makeMove(field);

			if (newnode->moveX_ == -1 && newnode->moveY_ == -1)
				this->findNewStep(field, newnode->moveX_, newnode->moveY_);

			if (current == bot1)
				current = bot2;
			else
				current = bot1;
		}

		// 4. Результаты из симуляции мы будем распространять от текущего до корня. 
		//Ко всем родительским узлам мы добавим единицу в количество сыгранных партий, 
		//а если мы наткнёмся на узел победителя — то в такой узел мы добавим единицу 
		//в количество выигранных партий.

		int winner = TTTGame::checkWin(field);

		Texture oPiece;
		oPiece.loadFromFile(O_PIECE_FILEPATH);

		MCBTreeNode * currentnode = newnode;
		while (currentnode != nullptr)
		{
			currentnode->attempts_++;

			if (currentnode->player_ == winner)
				currentnode->wins_++;

			currentnode = currentnode->parent_;
		}

		//проверяем можем ли мы сделать ход
		this->mCurrent_ = newnode;
		TTTGame::makeMove(someField, this->mFigure_, mCurrent_->moveX_, mCurrent_->moveY_, window, oPiece);
	}


	// сброс
	void reset() {
		this->mCurrent_ = this->mTree_;
		TTTGame::init(this->mPreviousStep_);
	}
};

#endif