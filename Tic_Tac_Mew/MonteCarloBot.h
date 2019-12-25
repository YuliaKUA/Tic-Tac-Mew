// algorithm
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
	int attempts_ = 0; // attempts

	MCBTreeNode * parent_ = nullptr;
	vector <MCBTreeNode *>  nodes_;

} MCBTreeNode;



////////////////////////
class MonteCarloBot : public Player
{
private:
	int mFigure_;

	// The state of the field in the previous step
	TTTGame::Field mPreviousStep_;

	// Search for the next step
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

	MCBTreeNode * mTree_; // Monte Carlo tree won back
	MCBTreeNode * mCurrent_; // current state tree

public:
	MonteCarloBot()
	{
		this->mFigure_ = 0; // cross or zero
		this->mTree_ = new MCBTreeNode;
		this->mCurrent_ = this->mTree_;
		TTTGame::init(this->mPreviousStep_);
	}

	void setFigure(int figure) { // set to 1 or 2
		this->mFigure_ = figure;
	}

	int getFigure() { // return the player’s piece
		return this->mFigure_;
	}

	void makeMove(TTTGame::Field & field) { }

	void makeMove(TTTGame::Field & someField, RenderWindow & window) { // make a move

		// add a node with a new move
		// the algorithm chooses the move of its opponent
		// If such a move exists - we will choose it, if not - add
		bool exist = false;

		int enemyX = -1, enemyY = -1; // enemy coordinates
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

		// 1. select the node with the most wins
		MCBTreeNode * bestnode = this->mCurrent_;
		for (MCBTreeNode * node : this->mCurrent_->nodes_)
		{
			if (((double)node->wins_ / node->attempts_) > ((double)bestnode->wins_ / bestnode->attempts_))
				bestnode = node;
		}

		// 2. extension - create a new node
		// To the selected node with the opponent’s move, we will add a node
		// with its own progress and with zero results
		MCBTreeNode * newnode = new MCBTreeNode;
		newnode->parent_ = bestnode;
		newnode->player_ = this->mFigure_;
		this->mCurrent_->nodes_.push_back(newnode);

		// 3. game simulation
		// Play the game from the current state of the playing field to someone else's victory.
		// From here we will take only the first move (i.e. our move) and the results
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

		// 4. Results from the simulation we will distribute from the current to the root.
		// To all parent nodes we add one to the number of games played,
		// and if we stumble upon a winner’s node, we will add a unit to such a node
		// in the number of games won.

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

		// check if we can make a move
		this->mCurrent_ = newnode;
		TTTGame::makeMove(someField, this->mFigure_, mCurrent_->moveX_, mCurrent_->moveY_, window, oPiece);
	}

	void reset() {
		this->mCurrent_ = this->mTree_;
		TTTGame::init(this->mPreviousStep_);
	}
};

#endif
