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

	//������ ������������ �������
	map <string, Texture> textures_;

public:

	//�������� �������� �� �����
	void loadTexture(const string& name, const string &filename);

	//����� ��������
	Texture& getRef(const string& texture);

	//�����������
	TextureManager() { }

	//����������
	~TextureManager() { }
};

#endif