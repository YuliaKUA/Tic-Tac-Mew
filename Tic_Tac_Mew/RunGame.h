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

// функция для первой обучающей игры бота с ботом
void simulationGame(TTTGame::Field &field, Player * player1, Player * player2) {
	//текущий игрок 
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


	SYSTEMTIME st; //системное время для рандома
	GetSystemTime(&st);
	srand(st.wMilliseconds);

	TTTGame::Field field;
	TTTGame::init(field);

	//создаем 2 игроков (бота и бота монте-карло) 
	//устанавливаем для каждого фигуру - крестик 1 или нолик 2
	Player * player1 = new Bot();
	player1->setFigure(TTT_CROSS);
	Player * player2 = new MonteCarloBot();
	player2->setFigure(TTT_CIRCLE);

	simulationGame(field, player1, player2);

	//текущий игрок 
	Player * current;

	player1 = new User(); // добавляем пользователя
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

	int whoWin = TTTGame::checkWin(field); //кто победил
	if (whoWin == TTT_EMPTY) {
		Sleep(500);
	}
	else {
		Sleep(1500);
	}

	// запуск анимации
	runAnimation(window, whoWin);

}

//функция запускает разную анимацию после завершения игры
// в зависимости от того, кто победил
void runAnimation(RenderWindow & window, int who) {
	Texture herotexture, winTex,
		retEnt;

	retEnt.loadFromFile(RETURN_MENU_ENTER);

	Sprite herosprite, winTexSprite,
		retEntSprite(retEnt);

	retEntSprite.setPosition(370, 660);

	int colorR, colorG, colorB, // определение цвета для заливки экрана
		frameX, frameY, //проход по картинке, по кадрам
		numFrames, // кол-во кадров
		height, width; //размер прямоугольника для выделения кадра

	//в зависимости от того, кто выиграл, загружаем разные изображения для анимации
	// + их индивидуальные настройки для вывода
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

	float CurrentFrame = 0; //хранит текущий кадр
	Clock clock;

	while (!Keyboard::isKeyPressed(Keyboard::Enter)) {
		window.setMouseCursorVisible(false);

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		//служит для прохождения по "кадрам". переменная доходит до (кол-ва кажров) 
		//суммируя произведение времени и скорости 
		//изменив 0.005 можно изменить скорость анимации
		CurrentFrame += 0.005*time;

		//проходимся по всем кадрам, если дошли до последнего - возвращаемся к первому
		if (CurrentFrame > numFrames) CurrentFrame -= numFrames;

		//проходимся по координатам Х
		herosprite.setTextureRect(IntRect(frameX * int(CurrentFrame), frameY, height, width));

		window.clear(Color(colorR, colorG, colorB));

		window.draw(herosprite);
		window.draw(winTexSprite);
		window.draw(retEntSprite);

		window.display();
	}
}