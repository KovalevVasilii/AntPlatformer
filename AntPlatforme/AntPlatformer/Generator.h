#pragma once
#include "Level.h"
#include<vector>
#include "SFML\Graphics.hpp"
#include "constants.h"
class Generator
{
public:
	Generator(int width, int height);
	~Generator();
	Level* generate();
	//std::vector<sf::Sprite>& get();
private:
	const int width;
	const int height;
	const int levels;
	const int m =  120;
	int heightLevel ;
	int widthLevel;
	//std::vector<sf::Sprite> sprites;
	Level level;
};

