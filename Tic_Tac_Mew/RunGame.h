#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <windows.h>

#include "TicTacToeGame.h"
#include "Player.h"
#include "MonteCarloBot.h"
#include "Game.h"

void runAnimation(RenderWindow & window, int who);

using namespace sf;
using namespace std;

// ������� ��� ������ ��������� ���� ���� � �����
void simulationGame(TTTGame::Field &field, Player * player1, Player * player2) {
	//������� ����� 
	Player * current = player1;

	for (int i = 0; i < POSSIBLE_MOVES; i++)
	{
		while (TTTGame::isPlayable(field))
		{
			current->makeMove(field);

			if (current == player1)
				current = player2;
			else
				current = player1;
		}

		player1->reset();
		player2->reset();
		TTTGame::init(field);
	}

}

void runGame(RenderWindow & window) {
	window.clear();

	Texture mainBack, grid;
	mainBack.loadFromFile(MAIN_BACKGROUND);
	grid.loadFromFile(GRID_SPRITE_FILEPATH);
	Sprite mainBg(mainBack), gameGrid(grid);
	window.draw(mainBg);
	gameGrid.setPosition(150, 75);
	window.draw(gameGrid);


	SYSTEMTIME st; //��������� ����� ��� �������
	GetSystemTime(&st);
	srand(st.wMilliseconds);

	TTTGame::Field field;
	TTTGame::init(field);

	//������� 2 ������� (���� � ���� �����-�����) 
	//������������� ��� ������� ������ - ������� 1 ��� ����� 2
	Player * player1 = new Bot();
	player1->setFigure(TTT_CROSS);
	Player * player2 = new MonteCarloBot();
	player2->setFigure(TTT_CIRCLE);

	simulationGame(field, player1, player2);

	//������� ����� 
	Player * current;

	player1 = new User(); // ��������� ������������
	player1->setFigure(TTT_CROSS);
	current = player1;

	bool flag = true;
	int temp = 0;
	while (TTTGame::isPlayable(field, window) && flag)
	{
		Event eventM;
		window.pollEvent(eventM);
		if (eventM.type == Event::KeyPressed) {
			return;
		}

		temp++;
		current->makeMove(field, window);

		window.display();

		if (eventM.type == Event::KeyPressed) {
			return;
		}

		while (!Mouse::isButtonPressed(Mouse::Left) == true && (temp % 2 == 0));

		Sleep(250);

		window.display();

		if (current == player1)
			current = player2;
		else
			current = player1;

		if (eventM.type == Event::KeyPressed) {
			return;
		}
	}

	window.display();

	int whoWin = TTTGame::checkWin(field); //��� �������
	if (whoWin == TTT_EMPTY) {
		Sleep(500);
	}
	else {
		Sleep(1500);
	}

	// ������ ��������
	runAnimation(window, whoWin);

}

//������� ��������� ������ �������� ����� ���������� ����
// � ����������� �� ����, ��� �������
void runAnimation(RenderWindow & window, int who) {
	Texture herotexture, winTex,
		retEnt;

	retEnt.loadFromFile(RETURN_MENU_ENTER);

	Sprite herosprite, winTexSprite,
		retEntSprite(retEnt);

	retEntSprite.setPosition(370, 660);

	int colorR, colorG, colorB, // ����������� ����� ��� ������� ������
		frameX, frameY, //������ �� ��������, �� ������
		numFrames, // ���-�� ������
		height, width; //������ �������������� ��� ��������� �����

	//� ����������� �� ����, ��� �������, ��������� ������ ����������� ��� ��������
	// + �� �������������� ��������� ��� ������
	if (who == TTT_CIRCLE) {
		winTex.loadFromFile(WIN_CIRCLE_TEXT);
		herotexture.loadFromFile(HERO_ANIMATION_WIN_CIRCLE);

		herosprite.setTexture(herotexture);
		winTexSprite.setTexture(winTex);

		herosprite.setTextureRect(IntRect(0, 0, 600, 600));
		colorR = 252;
		colorG = 238;
		colorB = 228;
		frameX = 566;
		frameY = 0;
		numFrames = 12;
		height = 600;
		width = 600;

		herosprite.setPosition(300, 50);
		winTexSprite.setPosition(390, 530);
	}
	else if (who == TTT_CROSS) {
		winTex.loadFromFile(WIN_CROSS_TEXT);
		herotexture.loadFromFile(HERO_ANIMATION_WIN_CROSS);

		herosprite.setTexture(herotexture);
		winTexSprite.setTexture(winTex);

		herosprite.setTextureRect(IntRect(0, 0, 600, 600));

		colorR = 254;
		colorG = 242;
		colorB = 230;
		frameX = 700;
		frameY = 0;
		numFrames = 8;
		height = 600;
		width = 600;

		herosprite.setPosition(260, 50);
		winTexSprite.setPosition(450, 600);
	}
	else {
		winTex.loadFromFile(NONE_WIN_TEXT);
		herotexture.loadFromFile(HERO_ANIMATION_NONE);

		herosprite.setTexture(herotexture);
		winTexSprite.setTexture(winTex);

		herosprite.setTextureRect(IntRect(0, 0, 600, 600));

		colorR = 255;
		colorG = 255;
		colorB = 255;
		frameX = 600;
		frameY = 0;
		numFrames = 4;
		height = 600;
		width = 600;

		herosprite.setPosition(300, 0);
		winTexSprite.setPosition(520, 580);
	}

	float CurrentFrame = 0; //������ ������� ����
	Clock clock;

	while (!Keyboard::isKeyPressed(Keyboard::Enter)) {
		window.setMouseCursorVisible(false);

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		//������ ��� ����������� �� "������". ���������� ������� �� (���-�� ������) 
		//�������� ������������ ������� � �������� 
		//������� 0.005 ����� �������� �������� ��������
		CurrentFrame += 0.005*time;

		//���������� �� ���� ������, ���� ����� �� ���������� - ������������ � �������
		if (CurrentFrame > numFrames) CurrentFrame -= numFrames;

		//���������� �� ����������� �
		herosprite.setTextureRect(IntRect(frameX * int(CurrentFrame), frameY, height, width));

		window.clear(Color(colorR, colorG, colorB));

		window.draw(herosprite);
		window.draw(winTexSprite);
		window.draw(retEntSprite);

		window.display();
	}
}