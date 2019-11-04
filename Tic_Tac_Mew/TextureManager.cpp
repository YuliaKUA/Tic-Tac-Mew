#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "TextureManager.h"

using namespace std;
using namespace sf;

void TextureManager::loadTexture(const string& name, const string& filename)
{
	//загружаем текстуру из файла
	Texture tex;
	tex.loadFromFile(filename);

	//Добавляем в массив с текстурами
	this->textures_[name] = tex;

}

Texture& TextureManager::getRef(const string& texture)
{
	return this->textures_.at(texture);
}

