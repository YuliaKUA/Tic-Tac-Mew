#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "TextureManager.h"

using namespace std;
using namespace sf;

void TextureManager::loadTexture(const string& name, const string& filename)
{
	// load the texture from the file
	Texture tex;
	tex.loadFromFile(filename);

	// add to the array with textures
	this->textures_[name] = tex;

}

Texture& TextureManager::getRef(const string& texture)
{
	return this->textures_.at(texture);
}

