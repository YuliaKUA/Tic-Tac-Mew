#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Game
{
private:
	void loadTextures();
public:

	Game();
	~Game();

	RenderWindow window_;

	TextureManager texmgr_;
	Sprite background_;

	void menu();
};

#endif