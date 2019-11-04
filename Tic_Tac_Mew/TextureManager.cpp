#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "TextureManager.h"

using namespace std;
using namespace sf;

void TextureManager::loadTexture(const string& name, const string& filename)
{
	//��������� �������� �� �����
	Texture tex;
	tex.loadFromFile(filename);

	//��������� � ������ � ����������
	this->textures_[name] = tex;

}

Texture& TextureManager::getRef(const string& texture)
{
	return this->textures_.at(texture);
}

