#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;
using namespace sf;

class TextureManager
{
private:

	//массив используемых текстур
	map <string, Texture> textures_;

public:

	//Добавить текстуру из файла
	void loadTexture(const string& name, const string &filename);

	//Вызов текстуры
	Texture& getRef(const string& texture);

	//Конструктор
	TextureManager() { }

	//Деструктор
	~TextureManager() { }
};

#endif